#include "gameLogic.h"
#include "collisionLogic.h"
#include "movementLogic.h"
#include "shootLogic.h"
#include "mouseInputs.h"
#include "gameObjects/powerUp.h"
#include "gameScreens/button.h"
#include "gameScreens/GameStates.h"
#include "system/collisionFunctions.h"
#include "system/draw.h"
#include "SFML/Audio.hpp"


using namespace GameObjects;
extern SpaceShip spaceShip;
extern Font customFont;
extern GameStates gameStates;
const int maxBigAsteroids = 4;
const int maxMediumAsteroids = 40;
const int maxSmallAsteroids = 80;
Asteroid specialAsteroid;
Asteroid bigAsteroids[maxBigAsteroids];
Asteroid mediumAsteroids[maxMediumAsteroids];
Asteroid smallAsteroids[maxSmallAsteroids];
PowerUp piercingPowerUp;
PowerUp sniperPowerUp;

Sound deathScream;
int mediumAsteroidCount = 0;
int smallAsteroidCount = 0;
int bigAsteroidsOnScreen = 4;
float highScore = 0.0f;
Texture livesTexture;
const char* playerScore;
const char* maxScore;


Button pauseMenuButton     ;
Button continueMenuButton  ;
Button restartMenuButton   ;
Button exitMenuButton      ;
bool isGamePaused = false;
bool isGameOver = false;
namespace GameLogic
{


	void initGame(RenderWindow& window)
	{
		isGameOver = false;
		bigAsteroidsOnScreen = 4;
		isGamePaused = false;
		float width = static_cast<float>(window.getSize().x);
		float height = static_cast<float>(window.getSize().y);
		isGamePaused = false;
		continueMenuButton = createButton(width / 2 - buttonWidth / 2 * static_cast<float>(window.getSize().x) / 1024, height / 2 - height / 8 * static_cast<float>(window.getSize().y) / 768, buttonWidth, buttonHeight, " CONTINUE", DARKGREEN);
		restartMenuButton = createButton(width / 3 + width / 4 - buttonWidth / 2 * static_cast<float>(window.getSize().x) / 1024, height / 2.0f - buttonHeight * static_cast<float>(window.getSize().y) / 768, buttonWidth, buttonHeight, " RESTART", DARKPURPLE);
		exitMenuButton = createButton(width / 3 + width / 8 - buttonWidth * static_cast<float>(window.getSize().x) / 1024, height / 2.0f - buttonHeight * static_cast<float>(window.getSize().y)) / 768, buttonWidth, buttonHeight, "   EXIT", RED);
		pauseMenuButton = createButton(width / 2 - buttonWidth / 2 * static_cast<float>(window.getSize().x) / 1024, 0 + buttonHeight / 2 * static_cast<float>(window.getSize().y) / 768, buttonWidth , buttonHeight , "  PAUSE", DARKGREEN);
		specialAsteroid = createSpecialAsteroid();
		resetAsteroid(specialAsteroid);

		specialAsteroid.isActive = true;
		for (int i = 0; i < maxSmallAsteroids; ++i)
		{
			if (i < maxBigAsteroids)
			{
				bigAsteroids[i] = createBigAsteroid();
				;
			}

			if (i < maxMediumAsteroids)
			{
				mediumAsteroids[i] = createMediumAsteroid();

			}

			smallAsteroids[i] = createSmallAsteroid();

		}
		float timer = static_cast<float>(GetRandomValue(20, 40));
		sniperPowerUp = createPowerUpSniper(timer);
		timer = static_cast<float>(GetRandomValue(20, 40));
		piercingPowerUp = createPowerUpPiercing(timer);
		Vector2f spacePosition = { (float)window.getSize().x / 2,(float)window.getSize().y / 2 };
		spaceShip = initSpaceShip(spacePosition, 0, 1);
		initBullets();
		highScore = static_cast<float>(LoadStorageValue(0));
	}
	void increaseAsteroidSpawn()
	{
		if (spaceShip.score >=5000)
		{
			bigAsteroidsOnScreen = 10;
		}
		if (spaceShip.score>2500)
		{
			bigAsteroidsOnScreen = 8;
		}
		if (spaceShip.score>2000)
		{
			bigAsteroidsOnScreen = 6;
		}
	}
	void resetGame()
	{
		isGamePaused = false;
		spaceShip.isDead = false;
		specialAsteroid = createSpecialAsteroid();
		resetAsteroid(specialAsteroid);

		specialAsteroid.isActive = true;

		for (int i = 0; i < maxSmallAsteroids; ++i)
		{
			if (i < maxBigAsteroids)
			{
				bigAsteroids[i] = createBigAsteroid();

			}
			if (i < maxMediumAsteroids)
			{
				mediumAsteroids[i] = createMediumAsteroid();

			}

			smallAsteroids[i] = createSmallAsteroid();

		}

		Vector2f spacePosition = { (float)window.getSize().x / 2,(float)window.getSize().y / 2 };
		resetSpaceShip(spaceShip, spacePosition);
		float timer = static_cast<float>(GetRandomValue(20, 40));
		sniperPowerUp = createPowerUpSniper(timer);
		 timer = static_cast<float>(GetRandomValue(20, 40));
		piercingPowerUp = createPowerUpPiercing(timer);
		initBullets();
		if (spaceShip.lives <= 0)
		{
			deathScream.play();
			if (spaceShip.score > highScore)
			{
				highScore = spaceShip.score;
				if (SaveStorageValue(0, static_cast<int>(highScore)))
				{
				}
			}
			isGameOver = true;
			
		}
	}
	void powerUpLogic()
	{
		if (!sniperPowerUp.isActive && !sniperPowerUp.isSpawned)
		{
			sniperPowerUp.timer -= GetFrameTime();
			if (sniperPowerUp.timer <= 0)
			{
				randomSpawn(sniperPowerUp);
			}
		}
		if (sniperPowerUp.isSpawned && powerUpSpaceShipCollision(sniperPowerUp))
		{
			spaceShip.bulletType = activatePowerUp(sniperPowerUp);
			sniperPowerUp.isSpawned = false;
		}
		else if (sniperPowerUp.isActive)
		{
			sniperPowerUp.timerActive -= GetFrameTime();
			if (sniperPowerUp.timerActive <= 0)
			{
				spaceShip.bulletType = BulletType::Default;
				deactivatePowerUp(sniperPowerUp);
			}
		}

		if (!piercingPowerUp.isActive && !piercingPowerUp.isSpawned)
		{
			piercingPowerUp.timer -= GetFrameTime();
			if (piercingPowerUp.timer <= 0)
			{
				randomSpawn(piercingPowerUp);
			}
		}
		if (piercingPowerUp.isSpawned && powerUpSpaceShipCollision(piercingPowerUp))
		{
			piercingPowerUp.isSpawned = false;
			spaceShip.bulletType = activatePowerUp(piercingPowerUp);
		}
		else if (piercingPowerUp.isActive)
		{
			piercingPowerUp.timerActive -= GetFrameTime();
			if (piercingPowerUp.timerActive <= 0)
			{
				spaceShip.bulletType = BulletType::Default;
				deactivatePowerUp(piercingPowerUp);
			}
		}

	}
	void playGame()
	{
#if _DEBUG
		if (IsKeyPressed(KEY_P))
		{

			spaceShip.isDead = true;

		}
		else if (IsKeyPressed(KEY_O))
		{

			spaceShip.bulletType = BulletType::Sniper;
		}

#endif

		if (isGameOver)
		{
			if (isPointRecColliding(Inputs::getMouseInput(), exitMenuButton.rec))
			{
				exitMenuButton.isOverThisButton = true;


				if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
				{

					setGameState(GameStates::Menu);
				}

			}
			else
			{
				exitMenuButton.isOverThisButton = false;
			}
			if (isPointRecColliding(Inputs::getMouseInput(), restartMenuButton.rec))
			{
				restartMenuButton.isOverThisButton = true;


				if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
				{

					initGame();

				}

			}
			else
			{
				restartMenuButton.isOverThisButton = false;
			}
		}
		else if (spaceShip.isDead)
		{
			updateShip();
			static float animTimer = 2;
			animTimer-= GetFrameTime();
			if (animTimer <= 0)
			{
				resetGame();
				animTimer = 2;
			}

		}
		else if (!isGamePaused)
		{
			increaseAsteroidSpawn();
			updateShootTimer();
			if (isPointRecColliding(Inputs::getMouseInput(), pauseMenuButton.rec))
			{
				pauseMenuButton.isOverThisButton = true;


				if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
				{

					isGamePaused = true;
				}

			}
			else
			{
				pauseMenuButton.isOverThisButton = false;
			}

			GameLogic::moveSpaceShip(spaceShip);
			changeAsteroidPosition(specialAsteroid);
			for (int i = 0; i < maxBullets; i++)
			{
				changeBulletPosition(spaceShip.bullet[i]);
			}
			for (int i = 0; i < maxBigAsteroids; i++)
			{
				changeAsteroidPosition(bigAsteroids[i]);
			}
			for (int i = 0; i < maxMediumAsteroids; ++i)
			{
				changeAsteroidPosition(mediumAsteroids[i]);
			}
			for (int i = 0; i < maxSmallAsteroids; ++i)
			{
				changeAsteroidPosition(smallAsteroids[i]);
			}

			GameLogic::updateCurrentSpaceShipPos(spaceShip);
			updateShip();
			powerUpLogic();
			updateBullet();
			shootBullets();
			changeShipPosition();
			for (int i = 0; i < maxBullets; i++)
			{
				GameLogic::moveAsteroidAcrossScreen(specialAsteroid);
				if (GameLogic::asteroidSpaceShipCollision(specialAsteroid))
				{
					spaceShip.isDead = true;
				}
				GameLogic::asteroidBulletCollision(specialAsteroid, spaceShip.bullet[i]);

				for (int j = 0; j < maxBigAsteroids; j++)
				{
					GameLogic::moveAsteroidAcrossScreen(bigAsteroids[i]);
					if (GameLogic::asteroidSpaceShipCollision(bigAsteroids[i]))
					{
						spaceShip.isDead = true;
					}

					GameLogic::asteroidBulletCollision(bigAsteroids[j], spaceShip.bullet[i]);

				}

				for (int j = 0; j < maxMediumAsteroids; j++)
				{
					GameLogic::moveAsteroidAcrossScreen(mediumAsteroids[j]);
					if (GameLogic::asteroidSpaceShipCollision(mediumAsteroids[j]))
					{
						spaceShip.isDead = true;
					}
					GameLogic::asteroidBulletCollision(mediumAsteroids[j], spaceShip.bullet[i]);


				}
				for (int j = 0; j < maxSmallAsteroids; j++)
				{
					GameLogic::moveAsteroidAcrossScreen(smallAsteroids[j]);
					if (GameLogic::asteroidSpaceShipCollision(smallAsteroids[j]))
					{
						spaceShip.isDead = true;
					}
					GameLogic::asteroidBulletCollision(smallAsteroids[j], spaceShip.bullet[i]);
				}

			}
			for (int j = 0; j < bigAsteroidsOnScreen ; ++j)
			{

				if (!bigAsteroids[j].isActive)
				{
					resetAsteroid(bigAsteroids[j]);
				}
			}


			updateSpecialAsteroid(specialAsteroid, spaceShip.position);
		}
		else if (isGamePaused)
		{

			if (isPointRecColliding(Inputs::getMouseInput(), exitMenuButton.rec))
			{
				exitMenuButton.isOverThisButton = true;


				if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
				{

					setGameState(GameStates::Menu);
				}

			}
			else
			{
				exitMenuButton.isOverThisButton = false;
			}
			if (isPointRecColliding(Inputs::getMouseInput(), continueMenuButton.rec))
			{
				continueMenuButton.isOverThisButton = true;


				if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
				{

					isGamePaused = false;
				}

			}
			else
			{
				continueMenuButton.isOverThisButton = false;
			}
			if (isPointRecColliding(Inputs::getMouseInput(), restartMenuButton.rec))
			{
				restartMenuButton.isOverThisButton = true;


				if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
				{

					initGame();

				}

			}
			else
			{
				restartMenuButton.isOverThisButton = false;
			}

		}

	}
	void drawPauseMenu()
	{
		
		
		drawButton(continueMenuButton);
		drawButton(restartMenuButton);
		drawButton(exitMenuButton);
	}
	void drawEndMenu()
	{
		sf::String a= String(playerScore);
		 sprintf(playerScore,"Score:%0.0F",static_cast<double>(spaceShip.score));
		Vector2f playerScoreMeasure = MeasureTextEx(customFont, playerScore, 50, 0);
		drawText(playerScore, window.getSize().x / 2 - playerScoreMeasure.x * 1.5f * static_cast<float>(window.getSize().x) / 1024, window.getSize().y / 2.5f - playerScoreMeasure.y , 50 * static_cast<float>(window.getSize().y) / 1024, BLACK, customFont,window);
		drawButton(restartMenuButton);
		drawButton(exitMenuButton);
	}
	void drawUI()
	{
		playerScore = TextFormat("Score:%0.0F", static_cast<double>(spaceShip.score));
		maxScore    = TextFormat("Max:%0.0F", static_cast<double>(highScore));
		Vector2f scoreMeasure = MeasureTextEx(customFont, playerScore, 50, 0);
		Vector2f maxScoreMeasure = MeasureTextEx(customFont, maxScore, 50, 0);
		drawText(playerScore, 0, 0, 50 * static_cast<float>(window.getSize().x) / 1024, BLACK, customFont);
		for (int i = 0; i < spaceShip.lives; i++)
		{
			drawTexture(livesTexture, { livesTexture.getSize().x * static_cast<float>(window.getSize().x) / 1024 * (i + 1.0f),scoreMeasure.y * static_cast<float>(window.getSize().y) / 768 }, 0, 1 * static_cast<float>(window.getSize().y) / 1024, WHITE);
		}
		drawText(maxScore, window.getSize().x - maxScoreMeasure.x * 1.5f * static_cast<float>(window.getSize().x) / 1024, 0, 50 * static_cast<float>(window.getSize().y) / 768, BLACK, customFont);
	}
	void drawGame()
	{

		for (int i = 0; i < maxBullets; ++i)
		{
			drawBullet(spaceShip.bullet[i]);
		}

		for (int i = 0; i < maxBigAsteroids; i++)
		{
			drawAsteroid(bigAsteroids[i]);

		}
		for (int i = 0; i < maxMediumAsteroids; ++i)
		{
			drawAsteroid(mediumAsteroids[i]);
		}
		for (int i = 0; i < maxSmallAsteroids; ++i)
		{

			drawAsteroid(smallAsteroids[i]);
		}
		drawAsteroid(specialAsteroid);
		if (sniperPowerUp.isSpawned)
		{
			drawPowerUp(sniperPowerUp);
		}
		if (piercingPowerUp.isSpawned)
		{
			drawPowerUp(piercingPowerUp);
		}
		drawShip();
		drawButtonTranslucent(pauseMenuButton);
		drawUI();
		if (spaceShip.isDead)
		{
			drawShip();
		}
		if (isGameOver)
		{
			drawEndMenu();
		}
		else if (isGamePaused)
		{
			drawPauseMenu();
		}
	}
}

