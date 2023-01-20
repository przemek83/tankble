#include "Brick.h"

Brick::Brick(Coordinates coordinates) : Tile(LOW_ARMOR, coordinates) {}

bool Brick::canFly() { return false; }

bool Brick::canDrive() { return false; }

ResourceType Brick::getResourceType() const { return ResourceType::BRICK; }
