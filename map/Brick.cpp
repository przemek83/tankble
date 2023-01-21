#include "Brick.h"

Brick::Brick(Point point) : Tile(LOW_ARMOR, point) {}

bool Brick::canFly() { return false; }

bool Brick::canDrive() { return false; }

ResourceType Brick::getResourceType() const { return ResourceType::BRICK; }
