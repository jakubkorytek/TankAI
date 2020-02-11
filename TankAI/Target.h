#pragma once
#include <Windows.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
class Target
{
private:
	int x, y;
public:
	Target();
	~Target();
	void createNew();
	void draw();
	int getX();
	int getY();
};

