#include "Bullet.h"



Bullet::Bullet()
{
	al_init();
	al_init_image_addon();
	isHere = false;
	score = 0;

}


Bullet::~Bullet()
{
}

bool Bullet::draw(int x, int y, float velocity, float angle, double gravity, Target *target)
{
	bool hitTheTarget = false;
	isHere = true;//po naciœniêciu spacji pocisk staje siê aktywny

	//pêtla wyœwietlaj¹ca po pixelu trajektoriê lotu
	int j = 0;
	for (int i = x; i < 1600; i++)
	{

		//obliczanie rzutu ukoœnego
		this->y = y - (j*tan(angle)) + (gravity*j*j) / (2 * velocity* velocity*cos(angle)*cos(angle));
		j++;
		//rysowanie
		al_draw_pixel(i, this->y, al_map_rgb(255, 255, 255));
		al_flip_display();

		//wykrywanie kolizji
		if (target->getX() == i && (target->getY() < this->y && (60 + target->getY()) > this->y))
		{
			hitTheTarget = true;
			target->createNew();//po wykryciu kolizji generujê now¹ tarczê strzelnicz¹
			score += 10;//zwiêkszam wynik
			isHere = false;
			break;
		}
		else if (y < 0 || y > 600 || i>1600)
		{
			isHere = false;
			break;
		}
	}
	isHere = false;
	
	return hitTheTarget;
}

void Bullet::destroy()
{
}


bool Bullet::hello()
{
	return this->isHere;
}

int Bullet::getScore()
{
	return this->score;
}
