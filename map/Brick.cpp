#include "Brick.h"

Brick::Brick(unsigned int x, unsigned int y) : Tile(LOW_ARMOR, x, y) {}

bool Brick::canFly() { return false; }

bool Brick::canDrive() { return false; }

ResourceType Brick::getResourceType() const { return ResourceType::BRICK; }
