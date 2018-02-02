#ifndef INPUTNEURON_HPP
#define INPUTNEURON_HPP

class InputNeuron : public Neuron
{
public:
    InputNeuron();

    InputNeuron(const InputNeuron &) = delete;
    InputNeuron(InputNeuron && r);

    InputNeuron & operator(const InputNeuron &) = delete;
    InputNeuron & operator(InputNeuron && r);

private:


};

#endif // INPUTNEURON_HPP
