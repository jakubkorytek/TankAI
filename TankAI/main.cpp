#include "Game.h"
#include "NeuralNetwork.h"
int main()
{
	NeuralNetwork neuralNetwork(5, 2, 5, 1);
	neuralNetwork.printNeuralNetwork();

	Game game;
	game.gameLoop();
}