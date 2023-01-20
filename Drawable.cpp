#include "Drawable.h"

Drawable::Drawable(Coordinates coordinates) : coordinates_(coordinates) {}

void Drawable::setX(unsigned int x) { coordinates_.x = x; }

void Drawable::setY(unsigned int y) { coordinates_.y = y; }
