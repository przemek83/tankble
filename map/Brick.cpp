#include "Brick.h"

#include "../Config.h"

Brick::Brick() : Tile(ResourceType::BRICK, Config::lowArmor) {}

bool Brick::canFly() { return false; }

bool Brick::canDrive() { return false; }
