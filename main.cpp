#include "LeakyNeuron.hpp"

void TriggerNeuralNet(std::vector<std::vector<LeakyNeuron *>> & neuralNet, const double & input);

int main (int argc, char * argv[])
{

    LeakyNeuron * input = new LeakyNeuron();
    LeakyNeuron * output1 = new LeakyNeuron();
    LeakyNeuron * output2 = new LeakyNeuron();
    LeakyNeuron * finalOutput = new LeakyNeuron();

    double edgeWeight1 = 200;
    double edgeWeight2 = 150;
    double edgeWeightFinal1 = 300;
    double edgeWeightFinal2 = 6000;

    input->connectOutput(output1, edgeWeight1);
    input->connectOutput(output2, edgeWeight2);
    output1->connectOutput(finalOutput, edgeWeightFinal1);
    output2->connectOutput(finalOutput, edgeWeightFinal2);

    std::vector<std::vector<LeakyNeuron *>> neuralNet;
    neuralNet.resize(3);
    neuralNet[0].resize(1);
    neuralNet[0][0] = input;
    neuralNet[1].resize(2);
    neuralNet[1][0] = output1;
    neuralNet[1][1] = output2;
    neuralNet[2].resize(1);
    neuralNet[2][0] = finalOutput;

    std::cout << "Connected input to output." << std::endl;
    std::cout << "Total Neurons: " << Neuron::totalObjects() << std::endl;

    TriggerNeuralNet(neuralNet, 1.0);

    TriggerNeuralNet(neuralNet, 0.01);
/*
    std::cout << "Input Node: \n" << input->printNode() << std::endl;
    std::cout << "Output Node: \n" << output->printNode() << std::endl;


    ///TEST Potential

    std::cout << "Input Potential: " << input->potential() << std::endl;
    std::cout << "Output Potential: " << output->potential() << std::endl;

    std::cout << "Firing!" << std::endl;
    input->addPotential(1.0);

    std::cout << "Input Potential: " << input->potential() << std::endl;
    std::cout << "Output Potential: " << output->potential() << std::endl;

    std::cout << "Feeding forward!" << std::endl;
    input->feedForward();

    std::cout << "Input Potential: " << input->potential() << std::endl;
    std::cout << "Output Potential: " << output->potential() << std::endl;

    ///DISCONNECT

    input->disconnectOutput(output);

    std::cout << "Disconnected nodes." << std::endl;

    if (input) {
      std::cout << "Input Node: \n" << input->printNode() << std::endl;
    } else {
      std::cout << "Input Node deleted." << std::endl;
    }
    if (output) {
      std::cout << "Output Node: \n" << output->printNode() << std::endl;
    } else {
      std::cout << "Output Node deleted." << std::endl;
    }

    delete input;
    delete output;
*/
    std::cout << "Total Neurons: " << Neuron::totalObjects() << std::endl;

    return 0;
}

void TriggerNeuralNet(std::vector<std::vector<LeakyNeuron *>> & neuralNet, const double & input) {
    std::cout << "Setting the input: " << input << std::endl;
    neuralNet[0][0]->addPotential(input);

    std::cout << "\nPotentials Before: " << std::endl;
    for (size_t i = 0; i < neuralNet.size(); i++) {
      for (size_t j = 0; j < neuralNet[i].size(); j++) {
        std::cout << "Layer " << i << ", Node " << j << ": " << neuralNet[i][j]->potential() << std::endl;
      }
    }
    std::cout << std::endl;

    for (size_t i = 0; i < neuralNet.size(); i++) {
      for (size_t j = 0; j < neuralNet[i].size(); j++) {
        //std::cout << "Before Layer " << i << ", Node " << j << ": " << neuralNet[i][j]->potential() << std::endl;
        neuralNet[i][j]->feedForward();
        //std::cout << "After Layer " << i << ", Node " << j << ": " << neuralNet[i][j]->potential() << std::endl;
      }
    }

    std::cout << "\nPotentials After: " << std::endl;

    for (size_t i = 0; i < neuralNet.size(); i++) {
      for (size_t j = 0; j < neuralNet[i].size(); j++) {
        std::cout << "Layer " << i << ", Node " << j << ": " << neuralNet[i][j]->potential() << std::endl;
      }
    }
    std::cout << std::endl;
}
