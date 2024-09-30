#include "Drawable.h"

Drawable::Drawable(Point point) : point_(point) {}

Drawable::~Drawable() = default;

int Drawable::getX() const { return point_.x_; }
void Drawable::setX(int x) { point_.x_ = x; }

int Drawable::getY() const { return point_.y_; }
void Drawable::setY(int y) { point_.y_ = y; }

void Drawable::setLocation(Point point) { point_ = point; }

Point Drawable::getLocation() const { return point_; }
