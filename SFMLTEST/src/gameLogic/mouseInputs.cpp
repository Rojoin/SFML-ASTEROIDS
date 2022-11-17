#include "mouseInputs.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

#include <SFML/Window/Mouse.hpp>

#include "gameScreens/button.h"


namespace Inputs
{
	sf::Vector2f getMouseInput(sf::RenderWindow window)
	{
		return window.get();
	}

	bool isMouseKeyDown(sf::Mouse::Button button)
	{
		bool isDown = false;
		if (sf::Mouse::isButtonPressed(button))
		{
			return true;
		}
		else return false;
	}

	bool isMouseKeyPressed(sf::Mouse::Button button)
	{
		if (sf::Mouse::isButtonPressed(button))
		{
			return true;
		}
		else return false;
	}
}


