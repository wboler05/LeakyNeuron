#ifndef NEURON_HPP
#define NEURON_HPP

#include <iostream>
#include <vector>
#include <cinttypes>
#include <stdexcept>

class Neuron
{
public:
    struct Connection
    {
        Neuron * neuron = nullptr;
        double edge_weight;
    };

    Neuron();
    virtual ~Neuron();

    Neuron(const Neuron &) = delete;
    Neuron(Neuron && r);

    Neuron & operator= (const Neuron &) = delete;
    Neuron & operator= (Neuron && r);

    Connection * connectInput(Neuron * n, const double & edgeWeight);
    void connectInput(Connection * connection);
    void disconnectInput(Neuron * n);

    Connection * connectOutput(Neuron * n, const double & edgeWeight);
    void connectOutput(Connection * connection);
    void disconnectOutput(Neuron * n);

    virtual void addPotential(const double & potential) {};
    virtual void feedForward() {};

    const double & potential() const
    {
        return m_potential;
    }
    const std::vector<Connection *> & inputs() const
    {
        return m_inputs;
    }
    const std::vector<Connection *> & outputs() const
    {
        return m_outputs;
    }

    static Connection * createConnection(Neuron * n, const double & edgeWeight);

    static const int & totalObjects()
    {
        return s_count;
    }

    std::string printInputs() const;
    std::string printOutputs() const;
    std::string printNode() const;

protected:
    int m_connections = 0;
    double m_potential = 0;
    std::vector<Connection *> m_inputs;
    std::vector<Connection *> m_outputs;

    static int s_count;

private:
    void eraseInputs();
    void eraseOutputs();
    void eraseConnections(std::vector<Connection *> & conVec);

    Connection * addConnectionToVector(
        Neuron * n,
        const double & edgeWeight,
        std::vector<Connection *> & conVec);

    void addConnectionToVector(
        Connection * c,
        std::vector<Connection *> & conVec);

    void disconnectConnectionFromVector(
        Neuron * n,
        std::vector<Connection *> & conVec);

};

#endif // NEURON_HPP
