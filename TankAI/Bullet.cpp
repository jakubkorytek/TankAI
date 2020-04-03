#include "Bullet.h"

bool Bullet::wasTargetHitted(int x, int y, Target *target)
{
	int tX = target->getX();
	int tY = target->getY();
	int height = target->getHeight();
	return	x == tX && y > tY && y < (tY + height);
}

bool Bullet::isOutOfWindow(int x, int y, int width, int height)
{
	return y > height || x > width;
}

Bullet::Bullet()
{
	al_init();
	al_init_image_addon();
	isMoving = false;
}


Bullet::~Bullet()
{
}

bool Bullet::draw(int x, int y, int width, int height, double power, float velocity,double degree, float angle, double gravity, Target *target)
{
	bool wasTargetReached = false;
	isMoving = true;//po naciœniêciu spacji pocisk staje siê aktywny

	int j = 0;
	for (int i = x; i < width; i++)
	{
		this->y = y - (j*tan(angle)) + (gravity*j*j) / (2 * (power*velocity)*(power*velocity)*cos(angle)*cos(angle));
		j++;

		al_draw_pixel(i, this->y, al_map_rgb(255, 255, 255));
		al_flip_display();

		if (target->getX() == i && (target->getY() < this->y && (60 + target->getY()) > this->y))
		{
			isMoving = false;
			wasTargetReached = true;
			score += 10;
			target->createNew();
			break;
		}
		else if (isOutOfWindow(i, this->y, width, height))
		{
			isMoving = false;
			break;
		}
	}
	isMoving = false;
	
	return wasTargetReached;
}

void Bullet::destroy()
{
}

bool Bullet::isCreated()
{
	return this->isMoving;
}

int Bullet::getScore()
{
	return this->score;
}

