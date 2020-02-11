#include "InputManager.h"



InputManager::InputManager()
{

}


InputManager::~InputManager()
{
}
//zarz�dzanie klawiatur�
bool InputManager::isKeyPressed(ALLEGRO_EVENT ev, int key)
{
	if (ev.type == ALLEGRO_EVENT_KEY_DOWN)//je�li zdarzenie to naci�ni�cie przycisku
	{
		if (ev.keyboard.keycode == key)//je�li naci�ni�ty przycisk to nasz szukany przycisk
			return true;
	}
	return false;
}

bool InputManager::isKeyPressed(ALLEGRO_EVENT ev, std::vector<int> keys)
{
	if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
	{
		for (int i = 0; i < keys.size(); i++)
		{
			if (ev.keyboard.keycode == keys[i])
				return true;
		}
	}
	return false;
}

bool InputManager::isKeyReleased(ALLEGRO_EVENT ev, int key)
{
	if (ev.type == ALLEGRO_EVENT_KEY_UP)//je�li zdarzenie to puszczenie przycisku
	{
		if (ev.keyboard.keycode == key)//je�li puszczony przycisk to nasz szukany przycisk
			return true;
	}
	return false;
}

bool InputManager::isKeyReleased(ALLEGRO_EVENT ev, std::vector<int> keys)
{
	if (ev.type == ALLEGRO_EVENT_KEY_UP)
	{
		for (int i = 0; i < keys.size(); i++)
		{
			if (ev.keyboard.keycode == keys[i])
				return true;
		}
	}
	return false;
}
