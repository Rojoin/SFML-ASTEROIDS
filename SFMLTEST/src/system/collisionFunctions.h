#pragma once
#include <SFML/Graphics/Rect.hpp>

#include "circle.h"

#include <SFML/System/Vector2.hpp>

using namespace sf;

bool isCircleCircleColliding(Circle circle1, Circle circle2);

bool isPointRecColliding(Vector2f mouse, IntRect rec);


