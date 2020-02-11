#pragma once
#include <allegro5/allegro_image.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
class Tank
{
private:
	int tankX, tankY;
	int barrelX, barrelY;
	float barrelAngle;
	ALLEGRO_BITMAP *tank;
	ALLEGRO_BITMAP *barrel;
	ALLEGRO_DISPLAY *display;

public:
	Tank();
	Tank(ALLEGRO_DISPLAY *display);
	~Tank();
	void setAngle(float angle);
	float getAngle();
	void draw();
	void destroy();
	void setDisplay(ALLEGRO_DISPLAY *display);
	int getBarrelX();
	int getBarrelY();
	int getBarrelWidth();
	
};

