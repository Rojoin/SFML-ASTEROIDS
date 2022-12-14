#include "collisionLogic.h"

#include <iostream>

#include "gameObjects/powerUp.h"
#include "system/collisionFunctions.h"
#include "gameObjects/spaceShip.h"
#include "SFML/Audio.hpp"


using namespace GameObjects;
extern SpaceShip spaceShip;
extern Asteroid mediumAsteroids[40];
extern Asteroid smallAsteroids[80];
extern int mediumAsteroidCount;
extern int smallAsteroidCount;
Sound collisionSound;

void GameLogic::asteroidBulletCollision(Asteroid& asteroid, Bullet& bullet)
{

	if (isCircleCircleColliding(asteroid.circle, bullet.circle) && bullet.isActive && asteroid.isActive)
	{
		deactivateAsteroid(asteroid);
		if (bullet.type != BulletType::Piercing)
		{
			deactivateBullet(bullet);
		}
		spaceShip.score += asteroid.points;
		collisionSound.play();
		if (asteroid.type == AsteroidType::Default)
		{
			activateNewAsteroids(asteroid, mediumAsteroids[mediumAsteroidCount], -1.0f);
			mediumAsteroidCount++;
			if (mediumAsteroidCount >= 40)
			{
				mediumAsteroidCount = 0;
			}
			activateNewAsteroids(asteroid, mediumAsteroids[mediumAsteroidCount], 1.0f);
			mediumAsteroidCount++;
			if (mediumAsteroidCount >= 40)
			{
				mediumAsteroidCount = 0;
			}
		}
		else if (asteroid.type == AsteroidType::Medium)
		{
			activateNewAsteroids(asteroid, smallAsteroids[smallAsteroidCount], -1);
			smallAsteroidCount++;
			if (smallAsteroidCount >= 80)
			{
				smallAsteroidCount = 0;
			}
			activateNewAsteroids(asteroid, smallAsteroids[smallAsteroidCount], 1);
			smallAsteroidCount++;
			if (smallAsteroidCount >= 80)
			{
				smallAsteroidCount = 0;
			}
		}
	}

}
bool GameLogic::powerUpSpaceShipCollision(PowerUp& powerUp)
{
	if (isCircleCircleColliding(powerUp.circle, spaceShip.circle))
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool GameLogic::asteroidSpaceShipCollision(Asteroid& asteroid)
{
	if (isCircleCircleColliding(asteroid.circle, spaceShip.circle) && asteroid.isActive)
	{
		return true;
	}
	return false;
}
