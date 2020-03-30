#pragma once

#include "InputLayer.h"
#include "Layer.h"
#include "TrainingData.h"

class NeuralNetwork
{
public:
	NeuralNetwork(int numberOfNeuralNetworkInputs, int numberOfHiddenLayers, int numberOfNeuronsInHiddenLayers, int numberOfNeuralNetworkOutputs);
	~NeuralNetwork();

	InputLayer inputLayer;
	vector<Layer> listOfHiddenLayers;
	Layer outputLayer;
	
	double learningRate = 0.2;

	void printNeuralNetwork();
	double guessResult(vector<double> inputs);
	void train(vector<TrainingData> trainingSet);
	void backpropagate(double error);

private:

};

inline NeuralNetwork::NeuralNetwork(int numberOfNeuralNetworkInputs, int numberOfHiddenLayers, int numberOfNeuronsInHiddenLayers, int numberOfNeuralNetworkOutputs)
{
	vector<Layer> tempHiddenLayers;
	for (int i = 0;i < numberOfHiddenLayers;++i)
	{
		Layer hiddenLayer;
		//First hidden layer, needs to fit to input layer
		if (i == 0)
		{
			hiddenLayer = Layer(numberOfNeuronsInHiddenLayers, numberOfNeuralNetworkInputs);
		}
		//If not, then hidden layer needs to fit other hidden layers
		else
		{
			hiddenLayer = Layer(numberOfNeuronsInHiddenLayers, numberOfNeuronsInHiddenLayers);
		}
		tempHiddenLayers.push_back(hiddenLayer);
	}
	this->listOfHiddenLayers = tempHiddenLayers;

	//Output layer needs to fit last hidden layer
	this->outputLayer = Layer(numberOfNeuralNetworkOutputs, numberOfNeuronsInHiddenLayers);
}

inline NeuralNetwork::~NeuralNetwork()
{
}

inline void NeuralNetwork::printNeuralNetwork()
{
	//this->inputLayer.printInputLayer();
	for (int i = 0; i < this->listOfHiddenLayers.size();++i)
	{
		cout << "Hidden layer " << i << endl;
		this->listOfHiddenLayers[i].printLayer();
	}
	this->outputLayer.printLayer();
}

inline double NeuralNetwork::guessResult(vector<double> inputs)
{
	vector<double> previousLayerOutputs;
	vector<double> output;
	this->inputLayer.feedInput(inputs);
	for (int i = 0; i < this->listOfHiddenLayers.size();++i)
	{
		//First hidden layer needs data from input layer
		if (i == 0)
		{
			vector<double> inputLayerOutputs = this->inputLayer.calculateLayerOutputData();
			previousLayerOutputs = this->listOfHiddenLayers[i].calculateLayerOutputData(inputLayerOutputs);
		}
		//next hidden layers take data from previous hidden layer
		else if (i < this->listOfHiddenLayers.size() - 1)
		{
			previousLayerOutputs = this->listOfHiddenLayers[i].calculateLayerOutputData(previousLayerOutputs);
		}
		else if (i == this->listOfHiddenLayers.size() - 1)
		{
			output = this->outputLayer.calculateLayerOutputData(previousLayerOutputs);
		}
	}
	return output[0];
}

inline void NeuralNetwork::train(vector<TrainingData> trainingSet)
{
	for (vector<TrainingData>::iterator trainingData = trainingSet.begin();trainingData != trainingSet.end();trainingData++)
	{
		double output = this->guessResult(trainingData->inputs);
		double error = pow(output - trainingData->output, 2);
	}
}
