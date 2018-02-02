#include "Neuron.hpp"

int Neuron::s_count = 0;

Neuron::Neuron() :
    m_connections(0),
    m_potential(0)
{
    s_count++;
}

Neuron::~Neuron()
{
    eraseInputs();
    eraseOutputs();
    s_count--;
}

Neuron::Neuron(Neuron && r) :
    m_connections(std::move(r.m_connections)),
    m_potential(std::move(r.m_potential)),
    m_inputs(std::move(r.m_inputs)),
    m_outputs(std::move(r.m_outputs))
{
    s_count++;
}

Neuron & Neuron::operator= (Neuron && r)
{
    m_connections = std::move(r.m_connections);
    m_potential = std::move(r.m_potential);
    m_inputs = std::move(r.m_inputs);
    m_outputs = std::move(r.m_outputs);
    return *this;
}

Neuron::Connection * Neuron::connectInput(Neuron * n, const double & edgeWeight)
{
    try
    {
        return addConnectionToVector(n, edgeWeight, m_inputs);
    }
    catch (const std::exception & e)
    {
        std::cerr << e.what() << " Neuron::connectInput(Neuron *, const double &)";
        exit(1);
    }
}

void Neuron::connectInput(Connection * connection)
{
    try
    {
        addConnectionToVector(connection, m_inputs);
    }
    catch (const std::exception & e)
    {
        std::cerr << e.what() << " Neuron::connectInput(Connection *)";
        exit(1);
    }
}

void Neuron::disconnectInput(Neuron * n)
{
    try
    {
        disconnectConnectionFromVector(n, m_inputs);
    }
    catch (const std::exception & e)
    {
        std::cerr << e.what() << " Neuron::disconnectInput(Neuron *)";
        exit(1);
    }
}

Neuron::Connection * Neuron::connectOutput(Neuron * n, const double & edgeWeight)
{
    try
    {
        if (n == nullptr)
        {
            throw std::runtime_error("Error, neuron is null.");
        }

        n->connectInput(this, edgeWeight);
        return addConnectionToVector(n, edgeWeight, m_outputs);
    }
    catch (const std::exception & e)
    {
        std::cerr << e.what() << " Neuron::connectInput()";
        exit(1);
    }
}

void Neuron::connectOutput(Connection * connection)
{
    try
    {
        if (connection == nullptr)
        {
            throw std::runtime_error("Error, connection is null.");
        }

        connection->neuron->connectInput(this, connection->edge_weight);
        addConnectionToVector(connection, m_outputs);
    }
    catch (const std::exception & e)
    {
        std::cerr << e.what() << " Neuron::connectInput(Connection *)";
        exit(1);
    }
}

void Neuron::disconnectOutput(Neuron * n)
{
    try
    {
        if (n == nullptr)
        {
            throw std::runtime_error("Error, neuron is null");
        }

        n->disconnectInput(this);
        disconnectConnectionFromVector(n, m_outputs);
    }
    catch (const std::exception & e)
    {
        std::cerr << e.what() << " Neuron::disconnectOut(Neuron *)";
        exit(1);
    }
}

Neuron::Connection * Neuron::addConnectionToVector(
    Neuron * n,
    const double & edgeWeight,
    std::vector<Connection *> & conVec)
{
    if (n == nullptr)
    {
        throw std::runtime_error("Error, neuron in null. Neuron::connectInput()");
        return nullptr;
    }
    for (size_t i = 0; i < conVec.size(); i++)
    {
        if (conVec[i]->neuron == n)
        {
            conVec[i]->edge_weight = edgeWeight;
            return conVec[i];
        }
    }

    try
    {
        Connection * newConnection = createConnection(n, edgeWeight);
        conVec.push_back(newConnection);
        return newConnection;
    }
    catch (const std::exception & e)
    {
        std::cerr << e.what() << " Neuron::addConnectionToVector()" << std::endl;
        exit(1);
    }
}

void Neuron::addConnectionToVector(
    Connection * c,
    std::vector<Connection *> & conVec)
{
    if (c == nullptr)
    {
        throw std::runtime_error("Error, connection is null.");
    }
    if (c->neuron == nullptr)
    {
        throw std::runtime_error("Error, neuron is null.");
    }

    for (size_t i = 0; i < conVec.size(); i++)
    {
        if (c == conVec[i])
        {
            return;
        }
        if (c->neuron == conVec[i]->neuron)
        {
            return;
        }
    }

    conVec.push_back(c);
    c->neuron->m_connections++;
}


Neuron::Connection * Neuron::createConnection(Neuron * n, const double & edgeWeight)
{
    if (n == nullptr)
    {
        throw std::runtime_error("Error, neuron is null. Neuron::createConnection()");
        return nullptr;
    }

    Connection * newConnection = new Connection();
    newConnection->neuron = n;
    newConnection->edge_weight = edgeWeight;
    n->m_connections++;
    return newConnection;
}

void Neuron::disconnectConnectionFromVector(Neuron * n, std::vector<Connection *> & conVec)
{
    if (n == nullptr)
    {
        throw std::runtime_error("Error, neuron is null. Neuron::disconnectConnectionFromVector()");
    }

    for (size_t i = 0; i < conVec.size(); i++)
    {
        if (conVec[i]->neuron == n)
        {
            conVec[i]->neuron->m_connections--;
//            if (conVec[i]->neuron->m_connections <= 0)
//            {
//                delete conVec[i]->neuron;
//                conVec[i]->neuron = nullptr;
//            }
            conVec[i]->neuron == nullptr;
            Connection * deleteMe = conVec[i];
            conVec.erase(conVec.begin() + i);
            delete deleteMe;
            return;
        }
    }

    throw std::runtime_error("Error, neuron not found. Neuron::disconnectConnectionFromVector()");
}

void Neuron::eraseInputs()
{
    eraseConnections(m_inputs);
}

void Neuron::eraseOutputs()
{
    eraseConnections(m_outputs);
}

void Neuron::eraseConnections(std::vector<Connection *> & conVec)
{
    while (conVec.size() > 0)
    {
        Connection * deleteMe = nullptr;

        if (conVec[0] != nullptr)
        {
            if (conVec[0]->neuron != nullptr)
            {
                conVec[0]->neuron->m_connections--;
//                if (conVec[0]->neuron->m_connections <= 0)
//                {
//                    delete conVec[0]->neuron;
//                    conVec[0]->neuron = nullptr;
//                }
                conVec[0]->neuron = nullptr;
            }
        }
        deleteMe = conVec[0];
        conVec.erase(conVec.begin());
        if (deleteMe != nullptr)
        {
            delete deleteMe;
            deleteMe = nullptr;
        }
    }
}

std::string Neuron::printInputs() const {
  std::string s("Inputs (");
  s.append(std::to_string(m_inputs.size()));
  s.append(")::\n");
  for (size_t i = 0; i < m_inputs.size(); i++) {
    s.append(std::to_string((int)m_inputs[i]->neuron));
    s.append(": ");
    s.append(std::to_string(m_inputs[i]->edge_weight));
    s.append("\n");
  }
  s.append("\n");
  return s;
}

std::string Neuron::printOutputs() const {
  std::string s("Outputs (");
  s.append(std::to_string(m_outputs.size()));
  s.append(")::\n");
  for (size_t i = 0; i < m_outputs.size(); i++) {
    s.append(std::to_string((int)m_outputs[i]->neuron));
    s.append(": ");
    s.append(std::to_string(m_outputs[i]->edge_weight));
    s.append("\n");
  }
  s.append("\n");
  return s;
}

std::string Neuron::printNode() const {
  std::string s;
  s.append("Node ");
  s.append(std::to_string((int)this));
  s.append("\n");
  s.append(printInputs());
  s.append(printOutputs());
  return s;
}
