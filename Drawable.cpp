#include "Drawable.h"

Drawable::Drawable(Point point) : point_(point) {}

void Drawable::setX(unsigned int x) { point_.x = x; }

void Drawable::setY(unsigned int y) { point_.y = y; }

Point Drawable::getLocation() const { return point_; }
