#include "draw.h"


#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/System/Vector2.hpp>

using namespace sf;


static int width;
static int height;
void updateScale(sf::RenderWindow& window)
{
	width  = window.getSize().x * 1 / 1024;
	height = window.getSize().y * 1 / 768;
}
void drawTexture(sf::Texture texture, Vector2f position,float rotation,float scale, sf::Color tint, sf::RenderWindow& window)
{
	Sprite sprite = Sprite(texture);
	sprite.setPosition(position);
	sprite.setRotation(rotation);
	sprite.setScale(scale,scale);
	sprite.setColor(tint);
	window.draw(sprite);
	

}

sf::String floatToString(float x)
{
	return 
}

void drawTexture(sf::Texture texture,sf::IntRect source,sf::IntRect dest, Vector2f position, float rotation,float scale, sf::Color tint, sf::RenderWindow& window)
{
	position.x *= scale;
	position.y *= scale;
	Sprite sprite = Sprite(texture);
	sprite.setTextureRect(source);
	sprite.setPosition(dest.left,dest.top);
	sprite.setOrigin(position);
	sprite.setRotation(rotation);
	sprite.setScale(scale, scale);
	sprite.setColor(tint);
	window.draw(sprite);
	//DrawTextureTiled(texture, source, dest, position, rotation,scale, tint);

}

void drawText(const char* text, float posX, float posY, float fontSize, sf::Color color, sf::Font font, sf::RenderWindow& window)
{
	sf::Text drawableText = sf::Text(text, font, fontSize);
	drawableText.setPosition(posX, posY);
	window.draw(drawableText);
}
 int getScaleWidth()
{
	return width;
}
 int getScaleHeight()
{
	return height;
}