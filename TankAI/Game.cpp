#include "Game.h"

void Game::aimHigher()
{
	degree += angleStep;
	if (degree > maxAngle)//biblioteka allegro obraca obiekty w ich praw¹ stronê czyli na logikê nasze 90 stopni to -90 dla biblioteki
		degree = maxAngle;
	recalculateBarrelXY();
}

void Game::aimLower()
{
	degree -= angleStep;
	if (degree < minAngle)
		degree = minAngle;
	recalculateBarrelXY();
}

void Game::recalculateBarrelXY()
{
	barrelY = tank.getBarrelWidth()* sin((degree*PI) / 180);//obliczanie pozycji koñca lufy z trygonometrii 
	barrelX = tank.getBarrelWidth()* cos((degree*PI) / 180);//145 to szerokoœæ grafiki lufy, 0.8 to jej skalowanie do rysowania
}

void Game::shot()
{
	if (!bullet.isCreated())//jeœli pocisk nie istnieje to zostanie wystrzelony, dziêki temu nie wystrzelê kilku pocisków na raz, w koñcu to czo³g a nie karabin :)
	{
		bool wasTargetReached = false;
		int x = tank.getBarrelX();
		int y = tank.getBarrelY();

		vector<double> inputs;
		inputs.push_back(MathUtils::normalize(x, screenWidth));
		inputs.push_back(MathUtils::normalize(y, screenHeight));
		inputs.push_back(MathUtils::normalize(target.getX(), screenWidth));
		inputs.push_back(MathUtils::normalize(target.getY(), screenHeight));
		inputs.push_back(MathUtils::normalize(target.getHeight(), screenHeight));
		inputs.push_back(MathUtils::normalize(gravity, 100.f));

		vector<double> outputs = neuralNetwork.feedForward(inputs);

		degree = MathUtils::denormalize(outputs[0], maxAngle);
		double radians = (degree * PI) / 180;
		power = (MathUtils::denormalize(outputs[1], maxPower));
		wasTargetReached = bullet.draw(x, y, screenWidth, screenHeight,power, velocity, degree, radians, gravity, &target);

		if (!wasTargetReached)
		{
			vector<double> correctOutput = TrainingData::getCorrectData(
				tank.getBarrelX(),
				tank.getBarrelY(),
				minAngle,
				maxAngle,
				angleStep,
				minPower,
				maxPower,
				powerStep,
				velocity,
				gravity,
				screenWidth,
				screenHeight
			);
 			neuralNetwork.backPropagate(correctOutput);
		}
		target.createNew();
		//double radians = (degree * PI) / 180;
		//draw(x, y, screenWidth, screenHeight, power, velocity, degree, radians, gravity, &target);
	}
}

vector<double> Game::prepareInputsForNeuralNetwork()
{
	vector<double> inputs{
		(double)tank.getBarrelX() + barrelX,
		(double)tank.getBarrelY() - barrelY,
		(double)target.getX(),
		(double)target.getY(),
		targetHeight,
	};
	return inputs;
}

Game::Game()
{
	target.createNew();
	al_init();//inicjalizacja biblioteki 
	al_init_font_addon();
	font = al_create_builtin_font();
	al_install_keyboard();
	al_init_image_addon();
	al_install_mouse();
	display = al_create_display(screenWidth, screenHeight);//tworzenie okna 1600x600
	al_set_window_title(display, "Tank");
	tank.setDisplay(display);
	done = false;
	timer = al_create_timer(1.0f / FPS);//kontrola fps
	queue = al_create_event_queue();//tworzenie kolejki wydarzeñ
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_start_timer(timer);

}

Game::~Game()
{
}

void Game::update()
{
	
}

void Game::draw()
{
		al_clear_to_color(al_map_rgb(0, 0, 0));//czyszczenie bitmapy 
		tank.draw();//rysowanie czo³gu
		target.draw();//rysowanie celów

		for (int i = 50; i < tank.getBarrelX() + barrelX; i++) //tu bylo rysowanie pomocniczego trójkata
		{
			al_draw_pixel(i, 530, al_map_rgb(255, 0, 255));
		}

		for (int i = 530; i > tank.getBarrelY() - barrelY; i--)
		{
			al_draw_pixel(tank.getBarrelX() + barrelX, i, al_map_rgb(255, 0, 255)); //tu bylo rysowanie pomocniczego trójkata
		}

		//wypisywanie danych
		{
			//snprintf metoda zamieniaj¹ca zmienne w tablice znaków
			snprintf(Angle, sizeof(Angle), "%g", (tank.getAngle() * -180) / PI);
			snprintf(Width, sizeof(Width), "%d", tank.getBarrelWidth());
			snprintf(PosX, sizeof(PosX), "%g", tank.getBarrelX() + barrelX);
			snprintf(PosY, sizeof(PosY), "%g", tank.getBarrelY() - barrelY);
			snprintf(bheight, sizeof(bheight), "%g", barrelX);
			snprintf(bwidth, sizeof(bwidth), "%g", barrelY);
			snprintf(powLvl, sizeof(powLvl), "%d", power);
			snprintf(score, sizeof(score), "%d", bullet.getScore());
			//tablice znaków s¹ potrzebne do wypisywania tekstu, innego typu danych ta funkcja nie przyjmuje
			al_draw_text(font, al_map_rgb(255, 255, 255), 10, 40, 0, "Poczatek lufy:");
			al_draw_text(font, al_map_rgb(255, 255, 255), 10, 60, 0, "X = 50  Y=530");
			al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 80, 0, "Kat = ");
			al_draw_textf(font, al_map_rgb(255, 255, 255), 100, 80, 0, Angle);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 100, 0, "Sila wystrzalu: ");
			al_draw_textf(font, al_map_rgb(255, 255, 255), 140, 100, 0, powLvl);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 120, 0, "Dlugosc lufy = ");
			al_draw_textf(font, al_map_rgb(255, 255, 255), 150, 120, 0, Width);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 140, 0, "Dlugosc a = ");
			al_draw_textf(font, al_map_rgb(255, 255, 255), 150, 140, 0, bwidth);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 160, 0, "Dlugosc b = ");
			al_draw_textf(font, al_map_rgb(255, 255, 255), 150, 160, 0, bheight);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 180, 0, "Polozenie konca lufy X = ");
			al_draw_textf(font, al_map_rgb(255, 255, 255), 220, 180, 0, PosX);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 200, 0, "Polozenie konca lufy Y = ");
			al_draw_textf(font, al_map_rgb(255, 255, 255), 220, 200, 0, PosY);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 760, 80, 0, "Wynik : ");
			al_draw_textf(font, al_map_rgb(255, 255, 255), 800, 100, 0, score);
		}
		al_flip_display();
}

void Game::destroy()
{
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);
	tank.destroy();
	bullet.destroy();
}

void Game::gameLoop(NeuralNetwork neuralNetwork)
{
	this->neuralNetwork = neuralNetwork;
	bool withTraining = true;

	vector<TrainingData> dataSet = TrainingData::generateTrainingData(
		tank.getBarrelX(),
		tank.getBarrelY(),
		20000, 
		minAngle,
		maxAngle,
		angleStep,
		minPower,
		maxPower,
		powerStep,
		velocity,
		gravity,
		screenWidth,
		screenHeight
	);
	for(int i = 0; i<5; i++)
	{
		random_shuffle(dataSet.begin(), dataSet.end());
		neuralNetwork.train(dataSet);
	}
	
	while (!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(queue, &ev);
		al_get_keyboard_state(&keyState);
		degree = (tank.getAngle() * -180) / PI;

		//Obs³uga klawiatury
		if (input.isKeyPressed(ev, ALLEGRO_KEY_ESCAPE))//warunek wyjœcia
			done = true;
		else if (input.isKeyPressed(ev, ALLEGRO_KEY_W))
		{
			aimHigher();
		}
		else if (input.isKeyPressed(ev, ALLEGRO_KEY_S))
		{
			aimLower();
		}
		else if (input.isKeyPressed(ev, ALLEGRO_KEY_D))
		{
			power += powerStep;
			if (power > maxPower)
				power = maxPower;
		}
		else if (input.isKeyPressed(ev, ALLEGRO_KEY_A))
		{
			power -= powerStep;
			if (power < minPower)
				power = minPower;
		}
	
		else if (input.isKeyPressed(ev, ALLEGRO_KEY_SPACE))
		{
			shot();
		}
		else if (input.isKeyPressed(ev, ALLEGRO_KEY_B))
		{
			isNeuralNetworkReady = !isNeuralNetworkReady;
		}
		else if (input.isKeyPressed(ev, ALLEGRO_KEY_K))
		{
			withTraining = !withTraining;
		}
		if (isNeuralNetworkReady)
		{
			//simulateNeuralNetworkPossibleMoves(withTraining);
		}
		tank.setAngle((degree * PI) / -180);//zamiana stopni na radiany 
		Game::draw();
	}
	Game::destroy();
}
