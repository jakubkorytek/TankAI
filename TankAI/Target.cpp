#include "Target.h"



Target::Target()
{
}


Target::~Target()
{
}

void Target::createNew()
{
	x = 400 + rand() % 600;//losowanie nowych wspó³rzêdnych
	y = 500 - rand() % 500;
}

void Target::draw()
{
	for (int i = 0; i < 60; i++)
		al_draw_pixel(x, y + i, al_map_rgb(255, 0, 0));//rysowanie tarczy strzeleckiej
}



int Target::getX()
{
	return this->x;
}

int Target::getY()
{
	return this->y;
}
