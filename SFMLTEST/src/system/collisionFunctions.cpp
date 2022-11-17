#include "collisionFunctions.h"

#include <SFML/Main.hpp>
#include <SFML/System/Vector2.hpp>


#include  "cmath"
using namespace sf;

bool isCircleCircleColliding(Circle circle1, Circle circle2)
{
	
	float distanceY = circle1.position.y -circle2.position.y;
	float distanceX = circle1.position.x -circle2.position.x;
	float distance = sqrt((distanceX* distanceX) + (distanceY*distanceY));

 	if (distance < circle1.radius + circle2.radius)
	{
		return true;
	}
	return false;
	
}

bool isPointRecColliding(Vector2f mouse, IntRect rec) //Check if works
{
	float rightEdge = rec.left + rec.width ;
	float leftEdge = rec.left;
	float upEdge = rec.top;
	float downEdge = rec.top + rec.height;

	if (mouse.x <= rightEdge && mouse.x >= leftEdge && mouse.y >= upEdge && mouse.y <= downEdge)
	{
		return true;
	}
	else
	{
		return false;
	}
}
