#include "Game.h"
#include "NeuralNetwork.h"
#include <chrono> 
#include <random>
#include "TrainingData.h"

using namespace std; 

int main()
{
	NeuralNetwork neuralNetwork(6, 4, 12, 2);
	neuralNetwork.printNeuralNetwork();


	Game game;
	game.gameLoop(neuralNetwork);
}