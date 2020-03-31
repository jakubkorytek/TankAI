#include "Game.h"
#include "NeuralNetwork.h"
#include <chrono> 
#include <random>
#include "TrainingData.h"

using namespace std; 

int main()
{
	NeuralNetwork neuralNetwork(10, 5, 5, 1);
	neuralNetwork.printNeuralNetwork();

	Game game;
	game.gameLoop(neuralNetwork);
}