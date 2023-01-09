#include "Steel.h"

#include "../Config.h"

Steel::Steel() : Tile(ResourceType::STEEL, Config::highArmor) {}

bool Steel::canFly() { return false; }

bool Steel::canDrive() { return false; }
