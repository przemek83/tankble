#include "Plant.h"

#include "../Config.h"

Plant::Plant() : Tile(ResourceType::PLANT, Config::noArmor) {}

bool Plant::canFly() { return true; }

bool Plant::canDrive() { return true; }
