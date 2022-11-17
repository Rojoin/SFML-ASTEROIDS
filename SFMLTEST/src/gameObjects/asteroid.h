#pragma once

#include <SFML/Graphics/Texture.hpp>

#include "GameObjectsEnums.h"
#include "system/circle.h"


namespace GameObjects
{
	struct Asteroid
	{
		GameObjects::AsteroidType type;
		sf::Texture texture;
		Circle circle;
		sf::Vector2ff aceleration;
		float rotation;
		float scale;
		float speed;
		float maxSpeed;
		float points;
		float currentTimer;
		bool isActive;
		sf::Vector2ff direction;
	};

	Asteroid createSpecialAsteroid();
	Asteroid createBigAsteroid();
	Asteroid createMediumAsteroid();
	void activateNewAsteroids(Asteroid& baseAsteroid, Asteroid& newAsteroid, float multiplier);
	Asteroid createSmallAsteroid();
	void changeAsteroidPosition(Asteroid& asteroid);
	void updateSpecialAsteroid(Asteroid& asteroid, sf::Vector2ff shipPos);
	void deactivateAsteroid(Asteroid& asteroid);
	void activateAsteroid(Asteroid& asteroid);
	void resetAsteroid(Asteroid& asteroid);
	void drawAsteroid(Asteroid& asteroid);
}