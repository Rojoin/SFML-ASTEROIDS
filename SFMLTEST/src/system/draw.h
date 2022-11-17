#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/System/Vector2.hpp>

using namespace sf;

void drawTexture(sf::Texture texture, sf::IntRect source, sf::IntRect dest, Vector2f position, float rotation, float scale, sf::Color tint, sf::RenderWindow& window);
void drawTexture(sf::Texture texture, Vector2f position, float rotation, float scale, sf::Color tint, sf::RenderWindow& window);
sf::String floatToString(float x);
void drawText(const char* text, float posX, float posY, float fontSize, sf::Color color, sf::Font font, sf::RenderWindow& window);
int  getScaleWidth();
int getScaleHeight();
void updateScale(sf::RenderWindow& window);
