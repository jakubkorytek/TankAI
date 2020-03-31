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

	InputLayer inputLayer;
	vector<Layer> listOfHiddenLayers;
	Layer outputLayer;
	
	
	double learningRate = 0.2;

	void printNeuralNetwork();
	double guessResult(vector<double> inputs);
	void train(vector<TrainingData> trainingSet);
	vector<double> backPropagateOutput(double expected);
	void backPropagateHidden(double error, vector<double> weights, double output, vector<double> inputs);

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
			vector<double> inputLayerOutputs = this->inputLayer.inputValues;
			previousLayerOutputs = this->listOfHiddenLayers[i].calculateLayerOutputData(inputLayerOutputs);
		}
		//next hidden layers take data from previous hidden layer
		else
		{
			previousLayerOutputs = this->listOfHiddenLayers[i].calculateLayerOutputData(previousLayerOutputs);
		}
	}
	output = this->outputLayer.calculateLayerOutputData(previousLayerOutputs);
	this->outputLayer.listOfNeurons[0].outputValue = output[0];
	return output[0];
}

inline void NeuralNetwork::train(vector<TrainingData> trainingSet)
{
	for (vector<TrainingData>::iterator trainingData = trainingSet.begin();trainingData != trainingSet.end();trainingData++)
	{
		
		double output = this->guessResult(trainingData->inputs);
		cout << "OUTPUT : " << output << endl;
		double error = trainingData->output - output;
		cout << "ERROR : " << error << endl;
		//vector<double> weightsDelta = backPropagateOutput(trainingData->output)
		this->backPropagateHidden(error, this->outputLayer.listOfNeurons[0].weightsIn, trainingData->output,  trainingData->inputs);
		cout << "AFTER TRAINING : " << endl;
		output = this->guessResult(trainingData->inputs);
		cout << "OUTPUT : " << output << endl;

		cout << "------------------------------------------------------------------------------" << endl;
	}
}

inline vector<double> NeuralNetwork::backPropagateOutput(double expected)
{
	double error = this->outputLayer.layerOutputs[0];
	double gamma = error * MathUtils::derivativeTanh(error);
	vector<double> weightsDelta;

	for (int i = 0; i < this->inputLayer.inputValues.size(); i++)
	{
		weightsDelta.push_back(gamma * this->inputLayer.inputValues[i]);
	}
	return weightsDelta;
}

inline void NeuralNetwork::backPropagateHidden(double error, vector<double> weights, double output, vector<double> inputs)
{
	vector<Neuron> secondLayer;
	vector<Neuron> firstLayer;
	vector<double> firstHiddenLayerOutputs;
	for (int i = 0; i < this->listOfHiddenLayers.size(); i++)
	{
		if (i == 0)
		{
			Layer layer = this->listOfHiddenLayers[i];
			firstLayer = layer.listOfNeurons;
			firstHiddenLayerOutputs = layer.calculateLayerOutputData(inputs);
		}
		else if (i == 1)
		{
			secondLayer = this->listOfHiddenLayers[i].listOfNeurons;
			for (vector<Neuron>::iterator neuron = secondLayer.begin();neuron != secondLayer.end();neuron++)
			{
				neuron->calculateOutputValue(firstHiddenLayerOutputs);
			}
		}
	}

	for (vector<Neuron>::iterator hiddenNeuron2 = secondLayer.begin();hiddenNeuron2 != secondLayer.end();hiddenNeuron2++)
	{
		hiddenNeuron2->error =  error * MathUtils::deriverateSigmoid(hiddenNeuron2->outputValue);
		for (int weight_x = 0; weight_x < hiddenNeuron2->weightsIn.size(); weight_x++)
		{
			hiddenNeuron2->weightsIn[weight_x] += learningRate * hiddenNeuron2->error*firstHiddenLayerOutputs[weight_x];
		}
		for (vector<Neuron>::iterator hiddenNeuron1 = firstLayer.begin();hiddenNeuron1 != firstLayer.end();hiddenNeuron1++)
		{
			hiddenNeuron1->error += hiddenNeuron2->error * MathUtils::deriverateSigmoid(hiddenNeuron1->outputValue);
			for (int weight_z = 0; weight_z < hiddenNeuron1->weightsIn.size(); weight_z++)
			{
				hiddenNeuron1->weightsIn[weight_z] += learningRate * hiddenNeuron1->error* inputs[weight_z];
			}
		}
	}
	this->listOfHiddenLayers[0].listOfNeurons = firstLayer;
	this->listOfHiddenLayers[1].listOfNeurons = secondLayer;
}

