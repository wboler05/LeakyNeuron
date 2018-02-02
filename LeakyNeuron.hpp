#ifndef LEAKYNEURON_HPP
#define LEAKYNEURON_HPP

#include "Neuron.hpp"
#include <cmath>

class LeakyNeuron : public Neuron
{
public:

    LeakyNeuron();
    ~LeakyNeuron();

    LeakyNeuron(const LeakyNeuron & r);
    LeakyNeuron(LeakyNeuron && r);

    LeakyNeuron & operator= (const LeakyNeuron & r) = delete;
    LeakyNeuron & operator= (LeakyNeuron && r);

    void addPotential(const double & potential);
    void feedForward();

    double activation(const double & input);

private:

};

#endif // LEAKYNEURON_HPP
