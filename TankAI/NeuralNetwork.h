#pragma once
#include "InputLayer.h"
#include "OutputLayer.h"
#include "HiddenLayer.h"

class NeuralNetwork
{
public:
	NeuralNetwork() {}
	~NeuralNetwork() {}

	NeuralNetwork initNetwork(size_t numberOfInputNeurons, size_t numberOfHiddenLayer, size_t numberOfNeuronInHiddenLayer, size_t numberOfOutputNeurons);

private:

};

