#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <cmath>
#include "Target.h"
#include "MathUtils.h"
#include <vector>
class Bullet
{
private:
	int x, y;
	int score;
	double angle;
	bool isMoving;
	bool wasTargetHitted(int x, int y, Target *target);
	bool isOutOfWindow(int x, int y, int width, int height);
	

public:
	Bullet();
	~Bullet();
	bool draw(int x,int startY,int width, int height, double power, float velocity, double degree, float angle, double gravity, Target *target);
	void destroy();
	bool isCreated();
	int getScore();
};

