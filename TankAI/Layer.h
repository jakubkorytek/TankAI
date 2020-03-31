#pragma once
#include "Neuron.h"
#include "MathUtils.h"

using namespace std;


class Layer
{
public:
	Layer(int numberOfNeuronsInLayer, int numberOfLayerInputs);
	Layer();
	~Layer();

	vector<Neuron> listOfNeurons;
	vector<double> layerInputs;
	vector<double> layerOutputs;

	int bias;

	vector<double> calculateLayerOutputData(vector<double> layerInputs);
	void printLayer();

private:

};

inline Layer::Layer(int numberOfNeuronsInLayer, int numberOfLayerInputs)
{
	this->bias = numberOfNeuronsInLayer;

	for (int i = 0;i < numberOfNeuronsInLayer;++i)
	{
		Neuron neuron(numberOfLayerInputs, bias);
		this->listOfNeurons.push_back(neuron);
	}
}

inline Layer::Layer()
{
}

inline Layer::~Layer()
{
}

inline vector<double> Layer::calculateLayerOutputData(vector<double> layerInputs)
{
	vector<double> tempLayerOutputs;
	for (vector<Neuron>::iterator neuron = listOfNeurons.begin();neuron != listOfNeurons.end();neuron++)
	{
		double outputValue = MathUtils::sigmoid(neuron->calculateOutputValue(layerInputs));
		neuron->outputValue = outputValue;
		tempLayerOutputs.push_back(outputValue);
	}
	this->layerOutputs = tempLayerOutputs;
	return this->layerOutputs;
}

inline void Layer::printLayer()
{
	for (int i=0; i<this->listOfNeurons.size();++i)
	{
		cout << "Neuron " << i << " outputs :" << endl; 
		this->listOfNeurons[i].printNeuron();
		cout << endl << endl;
	}
}
