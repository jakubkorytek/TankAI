#pragma once
#include <Windows.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
class Target
{
private:
	int x, y;
	int height = 50;
public:
	Target();
	~Target();
	void createNew();
	void draw();
	int getX();
	int getY();
	int getHeight() { return height; };
};

