#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/keyboard.h>
#include <allegro5/allegro_font.h>
#include "InputManager.h"
#include "Tank.h"
#include "Bullet.h"
#include "NeuralNetwork.h"
#include "TrainingData.h"

#include <cmath>
#include <string>
#include <sstream>
#include <algorithm>

#define PI 3.14
class Game
{
private:
	bool isNeuralNetworkReady = false;
	NeuralNetwork neuralNetwork;
	ALLEGRO_DISPLAY *display;
	float FPS = 1.0f;
	bool done = false;
	ALLEGRO_KEYBOARD_STATE keyState;
	ALLEGRO_TIMER *timer;
	ALLEGRO_EVENT_QUEUE *queue;
	InputManager input;
	Tank tank;
	int degree;
	int y;
	int power = 3;
	float barrelX, barrelY;
	float velocity = 10.0f;
	double gravity = 9.81;
	double targetHeight = 60;
	int maxPower = 20;
	int minPower = 1;
	int powerStep = 1;
	int maxAngle = 75;
	int minAngle = 0;
	int angleStep = 5;
	int screenHeight = 600;
	int screenWidth = 1000;
	int i;
	int gameScore = 0;
	Bullet bullet;
	Target target;
	ALLEGRO_FONT *font;
	//tablice znaków potrzebne do wypisywania zmiennych
	char Angle[3];
	char PosX[9];
	char PosY[9];
	char Width[6];
	char bheight[8];
	char bwidth[8];
	char score[5];
	char powLvl[3];
	void aimHigher();
	void aimLower();
	void recalculateBarrelXY();
	void shot();
	vector<double> prepareInputsForNeuralNetwork();

	
public:
	Game();
	~Game();
	void update();
	void draw();
	void destroy();
	void gameLoop(NeuralNetwork neuralNetwork);
};

