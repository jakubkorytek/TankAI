#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/keyboard.h>
#include <allegro5/allegro_font.h>
#include "InputManager.h"
#include "Tank.h"
#include "Bullet.h"

#include <cmath>
#include <string>
#include <sstream>
class Game
{
private:

	ALLEGRO_DISPLAY *display;
	float FPS = 10.0f;
	bool done = false;
	ALLEGRO_KEYBOARD_STATE keyState;
	ALLEGRO_TIMER *timer;
	ALLEGRO_EVENT_QUEUE *queue;
	InputManager input;
	Tank tank;
	const double pi = 3.14;
	double degree;
	int y;
	int power;
	float barrelX, barrelY;
	float velocity = 20.0f;
	double gravity = 9.81;
	int i;
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

	
public:
	Game();
	~Game();
	void update();
	void draw();
	void destroy();
	void gameLoop();
};

