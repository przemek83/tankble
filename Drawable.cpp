#include "Drawable.h"

Drawable::Drawable(unsigned int x, unsigned int y) : x_(x), y_(y) {}

void Drawable::setX(unsigned int x) { x_ = x; }

void Drawable::setY(unsigned int y) { y_ = y; }
