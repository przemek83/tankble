#include "Brick.h"

Brick::Brick() : Tile(ResourceType::BRICK, LOW_ARMOR) {}

bool Brick::canFly() { return false; }

bool Brick::canDrive() { return false; }
