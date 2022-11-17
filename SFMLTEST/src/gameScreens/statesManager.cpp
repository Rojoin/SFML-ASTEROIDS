#include <ctime>

#include "statesManager.h"
#include "GameStates.h"
#include "menuState.h"
#include "rulesState.h"
#include "creditsState.h"
#include "initialAnimationScreen.h"
#include "optionsState.h"
#include "gameObjects/spaceShip.h"
#include "gameLogic/gameLogic.h"
#include "system/draw.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Main.hpp>
#include <SFML/System/Vector2.hpp>

using namespace sf;


GameStates gameStates;
Texture wallpaper;
extern Texture creditsTexture;
extern Texture titleTexture;
extern Texture rulesTexture;
extern Texture shipTexture;
extern Texture bulletTexture;
extern Texture asteroidSpecialTexture;
extern Texture asteroidBigTexture;
extern Texture asteroidMediumTexture;
extern Texture asteroidSmallTexture;
extern Texture bulletSniperTexture;
extern Texture bulletPiercingTexture;
extern Texture powerUpSniperTexture;
extern Texture powerUpPiercingTexture;

extern Texture livesTexture;
extern Texture splashScreen;
extern Sound deathScream;
extern Sound bulletSniperSound;

extern Sound bulletPiercingSound;
extern Sound bulletDefaultSound;
extern Sound deathSound;
extern Sound collisionSound;
extern Font customFont;
Texture mouseCursor;
extern GameObjects::SpaceShip spaceShip;
Music mainTheme;
bool isProgramRunning = true;

int mousePosX;
int mousePosY;
 void logicProgram();
 void drawProgram();
 void loadResources();
 void unLoadResources();
 void loadTextures();
 void unLoadTextures();
 void unLoadAudio();
 void loadAudios();
 static void UpdateDrawFrame();
 void initProgram()
 {
	 setGameState(GameStates::InitialAnimation);
	 sf::RenderWindow window(sf::VideoMode(1024, 768), "The Last Slice");
	 window.setMouseCursorVisible(false);
	// InitAudioDevice();
	 loadResources();

	// SetExitKey(NULL);
	


	 isProgramRunning = true;
	// mainTheme = LoadMusicStream("resources/theLastSlice.mp3");


	 SetMusicVolume(mainTheme, 0.5);
	 PlayMusicStream(mainTheme);

#if defined(PLATFORM_WEB)
	
#else
	while (!WindowShouldClose() && isProgramRunning)
	{
		UpdateMusicStream(mainTheme);

		logicProgram();

		drawProgram();
	}
#endif
	unLoadResources();
	CloseWindow();
	CloseAudioDevice();
}

 void logicProgram()
{
	mousePosX = GetMouseX() - mouseCursor.width / 2;
	mousePosY = GetMouseY() - mouseCursor.height / 2;
	updateScale();
	switch (gameStates)
	{
	case GameStates::InitialAnimation:
		statesInitialAnimation();
		break;
	case GameStates::Menu:
		statesMenu(gameStates);
		break;
	case GameStates::Game:
		GameLogic::playGame();
		break;
	case GameStates::Rules:
		statesRules();
		break;
	case GameStates::Options:
		statesOptions();
		break;
	case GameStates::Credits:
		statesCredits();
		break;
	case GameStates::Exit:
		isProgramRunning = false;
		break;

	}
}

void drawProgram()
{
	BeginDrawing();
	ClearBackground(BLACK);
	DrawTexture(wallpaper, 0, 0, WHITE);
	switch (gameStates)
	{
	case GameStates::InitialAnimation:
		drawInitialAnimation();
		break;
	case GameStates::Menu:
		drawMenu();
		break;
	case GameStates::Game:
		GameLogic::drawGame();
		break;
	case GameStates::Rules:
		drawRules();
		break;
	case GameStates::Options:
		drawOptions();
		break;
	case GameStates::Credits:
		drawCredits();
		break;
	case GameStates::Exit:
		break;
	}
	DrawTexture(mouseCursor, mousePosX, mousePosY, WHITE);
	EndDrawing();
}

void loadAudios()
{
	collisionSound = LoadSound("resources/collision.wav");
	bulletDefaultSound = LoadSound("resources/bullet2.wav");
	deathSound = LoadSound("resources/explosion.wav");
	bulletPiercingSound = LoadSound("resources/shootPiercing.wav");
	bulletSniperSound = LoadSound("resources/shootSniper.wav");
	deathScream = LoadSound("resources/deathScream.wav");

}

 void loadTextures()
{
	livesTexture = LoadTexture("resources/lives.png");
	splashScreen = LoadTexture("resources/splashScreen.png");
	wallpaper = LoadTexture("resources/pizzaWallpaper.png");
	shipTexture = LoadTexture("resources/pizzaTiledMap.png");
	bulletTexture = LoadTexture("resources/olive.png");
	bulletSniperTexture = LoadTexture("resources/pineApple.png");
	bulletPiercingTexture = LoadTexture("resources/broccoli.png");
	asteroidSpecialTexture = LoadTexture("resources/specialAsteroidTiled.png");
	asteroidBigTexture = LoadTexture("resources/bigHand.png");
	asteroidMediumTexture = LoadTexture("resources/mediumHand.png");
	asteroidSmallTexture = LoadTexture("resources/smallHand.png");
	creditsTexture = LoadTexture("resources/credits.png");
	rulesTexture = LoadTexture("resources/rules.png");
	titleTexture = LoadTexture("resources/titleLogo.png");
	gameIcon = LoadImage("resources/titleLogo.png");
	mouseCursor = LoadTexture("resources/mousePointer.png");
	powerUpPiercingTexture = LoadTexture("resources/powerUpPiercing.png");
	powerUpSniperTexture = LoadTexture("resources/powerUpSniper.png");
	GenTextureMipmaps(&titleTexture);
	SetTextureFilter(titleTexture, TEXTURE_FILTER_ANISOTROPIC_16X);
	GenTextureMipmaps(&creditsTexture);
	SetTextureFilter(creditsTexture, TEXTURE_FILTER_ANISOTROPIC_16X);
	GenTextureMipmaps(&rulesTexture);
	SetTextureFilter(rulesTexture, TEXTURE_FILTER_ANISOTROPIC_16X);
}

 void loadResources()
{
	customFont = LoadFontEx("resources/LoftygoalsRegular-9Y5Xy.otf", 96, nullptr, 0);
	GenTextureMipmaps(&customFont.texture);
	SetTextureFilter(customFont.texture, TEXTURE_FILTER_ANISOTROPIC_16X);
	loadTextures();
	loadAudios();
}

void unLoadAudio()
{
	UnloadSound(collisionSound);
	UnloadSound(deathSound);
	UnloadSound(bulletDefaultSound);
	UnloadSound(bulletPiercingSound);
	UnloadSound(deathScream);
	UnloadSound(bulletSniperSound);
	UnloadMusicStream(mainTheme);
}
 void unLoadTextures()
{
	UnloadTexture(creditsTexture);
	UnloadTexture(asteroidBigTexture);
	UnloadTexture(asteroidSmallTexture);
	UnloadTexture(asteroidMediumTexture);
	UnloadTexture(asteroidSpecialTexture);
	UnloadTexture(bulletTexture);
	UnloadTexture(bulletSniperTexture);
	UnloadTexture(bulletPiercingTexture);
	UnloadTexture(shipTexture);
	UnloadTexture(wallpaper);
	UnloadTexture(splashScreen);
	UnloadTexture(livesTexture);
	UnloadTexture(titleTexture);
	UnloadTexture(rulesTexture);
	UnloadImage(gameIcon);
	UnloadTexture(mouseCursor);
}

void unLoadResources()
{
	//UnloadFont(customFont);
	unLoadAudio();
	unLoadTextures();

}