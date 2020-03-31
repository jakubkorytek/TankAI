#pragma once

#include "InputLayer.h"
#include "Layer.h"
#include "TrainingData.h"

class NeuralNetwork
{
public:
	NeuralNetwork() {};
	NeuralNetwork(int numberOfNeuralNetworkInputs, int numberOfHiddenLayers, int numberOfNeuronsInHiddenLayers, int numberOfNeuralNetworkOutputs);
	~NeuralNetwork();

	Layer inputLayer;
	vector<Layer> listOfHiddenLayers;
	Layer outputLayer;
	
	
	double learningRate = 0.2;

	vector<double> feedForward(vector<double> inputs);
	void backPropagate(vector<double> expected);
	void train(vector<TrainingData> trainingSet);
	void updateWeights();
	void printNeuralNetwork();

private:

};

inline NeuralNetwork::NeuralNetwork(int numberOfNeuralNetworkInputs, int numberOfHiddenLayers, int numberOfNeuronsInHiddenLayers, int numberOfNeuralNetworkOutputs)
{
	this->inputLayer = Layer(numberOfNeuralNetworkInputs, numberOfNeuralNetworkInputs);
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
	for (int i = 0; i < listOfHiddenLayers.size();++i)
	{
		cout << "Hidden layer " << i << endl;
		listOfHiddenLayers[i].printLayer();
	}
	outputLayer.printLayer();
}

inline vector<double> NeuralNetwork::feedForward(vector<double> inputs)
{
	inputLayer.feedForward(inputs);
	for (int i = 0; i < listOfHiddenLayers.size(); i++)
	{
		if (i == 0)
		{
			listOfHiddenLayers[i].feedForward(inputLayer.layerOutputs);
		}
		else
		{
			listOfHiddenLayers[i].feedForward(listOfHiddenLayers[i - 1].layerOutputs);
		}
	}
	outputLayer.feedForward(listOfHiddenLayers[listOfHiddenLayers.size() - 1].layerOutputs);
	return outputLayer.layerOutputs;
}

inline void NeuralNetwork::backPropagate(vector<double> expected)
{
	outputLayer.backPropagateOutput(expected);
	for (int i = listOfHiddenLayers.size() -1; i >= 0; i--)
	{
		if (i == listOfHiddenLayers.size() - 1)
		{
			listOfHiddenLayers[i].backPropagateHidden(outputLayer.listOfNeurons);
		}
	}
	updateWeights();
}

inline void NeuralNetwork::train(vector<TrainingData> trainingSet)
{
	for (int i = 0; i<trainingSet.size(); i++)
	{
		vector<double> outcome = feedForward(trainingSet[i].inputs);
		backPropagate(trainingSet[i].output);
		cout << "Expected : " << outcome[0] << endl;
		cout << "Should be : " << trainingSet[i].output[0] << endl;
		cout << "Error : " << trainingSet[i].output[0] - outcome[0] << endl;
		cout << "Training in progress ... " << endl;
		outcome = feedForward(trainingSet[i].inputs);
		cout << "Expectation after training : " << outcome[0] << endl;
		cout << "________________________________________________" << endl;
	}
}

inline void NeuralNetwork::updateWeights()
{
	for (int i = 0; i < inputLayer.listOfNeurons.size(); i++)
	{
		for (int j = 0; j < inputLayer.layerInputs.size(); j++)
		{
			inputLayer.listOfNeurons[i].weightsIn[j] -= inputLayer.listOfNeurons[i].weightsDelta[j] * learningRate;
		}
	}

	for (int i = 0; i < listOfHiddenLayers.size(); i++)
	{
		for (int j = 0; j < listOfHiddenLayers[i].listOfNeurons.size(); j++)
		{
			for (int x = 0; x < listOfHiddenLayers[i].layerInputs.size(); x++)
			{
				listOfHiddenLayers[i].listOfNeurons[j].weightsIn[x] -= listOfHiddenLayers[i].listOfNeurons[j].weightsDelta[x] * learningRate;
			}
		}
	}

	for (int i = 0; i < outputLayer.listOfNeurons.size(); i++)
	{
		for (int j = 0; j < outputLayer.layerInputs.size(); j++)
		{
			outputLayer.listOfNeurons[i].weightsIn[j] -= outputLayer.listOfNeurons[i].weightsDelta[j] * learningRate;
		}
	}
}


