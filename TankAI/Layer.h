#pragma once
#include "Neuron.h"
#include "MathUtils.h"

using namespace std;


class Layer
{
public:
	Layer(int numberOfNeuronsInLayer, int numberOfLayerInputs);
	Layer() {};
	~Layer() {};

	vector<Neuron> listOfNeurons;
	vector<double> layerInputs;
	vector<double> layerOutputs;

	vector<double> feedForward(vector<double> layerInputs);
	void backPropagateOutput(vector<double> expected);
	void backPropagateHidden(vector<Neuron> layerForward);
	void printLayer();

private:

};

inline Layer::Layer(int numberOfNeuronsInLayer, int numberOfLayerInputs)
{
	for (int i = 0;i < numberOfNeuronsInLayer;++i)
	{
		Neuron neuron(numberOfLayerInputs);
		this->listOfNeurons.push_back(neuron);
	}
}

inline vector<double> Layer::feedForward(vector<double> layerInputs)
{
	layerOutputs.clear();
	this->layerInputs = layerInputs;
	for (int i=0; i < listOfNeurons.size(); i++)
	{
		listOfNeurons[i].calculateOutputValue(layerInputs);
		layerOutputs.push_back(listOfNeurons[i].outputValue);
	}
	return layerOutputs;
}

inline void Layer::backPropagateOutput(vector<double> expected)
{
	for (int i = 0; i < listOfNeurons.size(); i++)
	{
		listOfNeurons[i].error = listOfNeurons[i].outputValue - expected[i];
	}

	for (int i = 0; i < listOfNeurons.size(); i++)
	{
		listOfNeurons[i].gamma = listOfNeurons[i].error * MathUtils::derivativeTanh(listOfNeurons[i].outputValue);
	}

	for (int i = 0; i < listOfNeurons.size(); i++)
	{
		for (int j = 0; j < layerInputs.size(); j++)
		{
			listOfNeurons[i].weightsDelta[j] = listOfNeurons[i].gamma * layerInputs[j];
		}
	}
}

inline void Layer::backPropagateHidden(vector<Neuron> layerForward)
{
	for (int i = 0; i < listOfNeurons.size(); i++)
	{
		listOfNeurons[i].gamma = 0;
		for (int j = 0; j < layerForward.size(); j++)
		{
			listOfNeurons[i].gamma += layerForward[j].gamma * layerForward[j].weightsIn[i];
		}
		listOfNeurons[i].gamma *= tanh(listOfNeurons[i].outputValue);
	}

	for (int i = 0; i < listOfNeurons.size();i++)
	{
		for (int j = 0; j < layerInputs.size(); j++)
		{
			listOfNeurons[i].weightsDelta[j] = listOfNeurons[i].gamma * layerInputs[j];
		}
	}
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
