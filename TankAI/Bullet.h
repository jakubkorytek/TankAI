#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <cmath>
#include "Target.h"
class Bullet
{
private:
	int x, y;
	double angle;
	bool isHere;
	int score;
	

public:
	Bullet();
	~Bullet();
	bool draw(int x,int y, float velocity,float angle, double gravity, Target *target);
	void destroy();
	bool hello();
	int getScore();

};

