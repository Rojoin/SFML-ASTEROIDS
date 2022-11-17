#pragma once
#include <SFML/System/Vector2.hpp>



namespace Inputs
{
	sf::Vector2f getMouseInput();
	bool isMouseKeyDown(int mouse);
	bool isMouseKeyPressed(int mouse);
}



