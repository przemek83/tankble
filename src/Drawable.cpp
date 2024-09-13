#include "Drawable.h"

Drawable::Drawable(Point point) : point_(point) {}

Drawable::~Drawable() = default;

void Drawable::setX(int x) { point_.x_ = x; }

void Drawable::setY(int y) { point_.y_ = y; }

void Drawable::setLocation(Point point) { point_ = point; }

Point Drawable::getLocation() const { return point_; }
