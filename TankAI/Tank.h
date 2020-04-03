#pragma once
#include <allegro5/allegro_image.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include "MathUtils.h"

class Tank
{
private:
	int tankX, tankY;
	int barrelX = 50, barrelY = 530;
	float barrelAngle = 0;
	ALLEGRO_BITMAP *tank;
	ALLEGRO_BITMAP *barrel;
	ALLEGRO_DISPLAY *display;

public:
	Tank();
	~Tank() {};
	void setAngle(float angle);
	float getAngle();
	void draw();
	void destroy();
	void setDisplay(ALLEGRO_DISPLAY *display);
	int getBarrelX();
	int getBarrelY();
	int getBarrelWidth();
	
};

