#include "LeakyNeuron.hpp"


LeakyNeuron::LeakyNeuron() :
  Neuron()
{

}

LeakyNeuron::~LeakyNeuron()
{

}

LeakyNeuron::LeakyNeuron(LeakyNeuron && r) :
  Neuron(std::move(r))
{

}

LeakyNeuron & LeakyNeuron::operator= (LeakyNeuron && r)
{
  Neuron::operator=(std::move(r));
  return *this;
}

void LeakyNeuron::addPotential(const double & potential)
{
  m_potential += potential;
}

void LeakyNeuron::feedForward()
{
  if (m_outputs.size() == 0) return;

  double outputPotential = m_potential * activation(m_potential);
  double totalWeight = 0.0;

  for (size_t i = 0; i < m_outputs.size(); i++) {
    totalWeight += m_outputs[i]->edge_weight;
  }

  for (size_t i = 0; i < m_outputs.size(); i++) {
    m_outputs[i]->neuron->addPotential(outputPotential * (m_outputs[i]->edge_weight / totalWeight));
  }

  m_potential -= outputPotential;
}

double LeakyNeuron::activation(const double & input)
{
  return 1.0 - ( 1.0 / (1 + exp(-input)) );
}
