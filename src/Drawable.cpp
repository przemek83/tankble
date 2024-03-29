#include "Drawable.h"

Drawable::Drawable(Point point) : point_(point) {}

Drawable::~Drawable() = default;

void Drawable::setX(unsigned int x) { point_.x = x; }

void Drawable::setY(unsigned int y) { point_.y = y; }

void Drawable::setLocation(Point point) { point_ = point; }

Point Drawable::getLocation() const { return point_; }
