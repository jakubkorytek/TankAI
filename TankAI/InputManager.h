#pragma once
#include <allegro5/allegro.h>
#include <allegro5/keyboard.h>
#include <vector>

class InputManager
{
private:
	ALLEGRO_KEYBOARD_STATE keyState;
public:
	InputManager();
	~InputManager();

	bool isKeyPressed(ALLEGRO_EVENT ev, int key);
	bool isKeyPressed(ALLEGRO_EVENT ev, std::vector<int> keys);

	bool isKeyReleased(ALLEGRO_EVENT ev, int key);
	bool isKeyReleased(ALLEGRO_EVENT ev, std::vector<int> keys);
};

