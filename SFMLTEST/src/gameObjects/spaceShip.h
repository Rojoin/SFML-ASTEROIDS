#pragma once
#include <raylib.h>
#include "Bullets.h"

namespace GameObjects
{


	struct SpaceShip
	{
		Vector2f position;
		Bullet bullet[20];
		BulletType bulletType;
		int bulletIndex = 0;
		Vector2f aceleration;
		Texture texture;
		int textureIndex;
		float rotation;
		float scale;
		float maxSpeed;
		float score;
		int lives;
		bool isDead;
		Sound deathSound;
		Rectangle source;
		Rectangle dest;
		Circle circle;
		Vector2f direction;
	};

	SpaceShip initSpaceShip( Vector2f position, float rotation, float scale);

	void updateShip();
	void drawShip();
	void changeShipPosition();
	void updateBullet();
	void updateShootTimer();
	void activateBullet();
	void deactivateBullet(GameObjects::Bullet& bullet);
	void resetSpaceShip(SpaceShip& ship, Vector2f position);
	void activatetBulletPowerUp();
	void deActivateBulletPowerUp();
	void initBullets();
	void drawShipDestruction();

}
