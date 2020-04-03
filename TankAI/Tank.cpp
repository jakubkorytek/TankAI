#include "Tank.h"

Tank::Tank()
{
	al_init();
	al_init_image_addon();

	tank = al_load_bitmap("C:/Users/jkorytek001/source/repos/Project5/Project5/tank.png");//³adowanie pliku png
	if (!tank)
		al_show_native_message_box(display, "ERROR", "NIE MOZNA", "OTWORZYC PLIKU TANK",NULL, NULL);

	barrel = al_load_bitmap("C:/Users/jkorytek001/source/repos/Project5/Project5/barrel.png");//³adowanie pliku png
	if(!barrel)
		al_show_native_message_box(display, "ERROR", "NIE MOZNA", "OTWORZYC PLIKU BARREL", NULL, NULL);
}

void Tank::setAngle(float angle)
{
	barrelAngle = angle;
}

float Tank::getAngle()
{
	return barrelAngle;
}


void Tank::draw()
{
	al_draw_scaled_rotated_bitmap(barrel, 0, 0, barrelX, barrelY, 0.2, 0.1, barrelAngle, NULL);//rysowanie bitmapy 
	al_draw_scaled_bitmap(tank, 0, 10, 145, 129, 0, 500, 100, 100, NULL);
}

void Tank::destroy()
{
	al_destroy_bitmap(tank);
	al_destroy_bitmap(barrel);
}

void Tank::setDisplay(ALLEGRO_DISPLAY * display)
{
	this->display = display;
}

int Tank::getBarrelX()
{
	return this->barrelX;
}

int Tank::getBarrelY()
{
	return this->barrelY;
}

int Tank::getBarrelWidth()
{
	return (int)al_get_bitmap_width(barrel) * 0.2;
}


