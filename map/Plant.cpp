#include "Plant.h"

Plant::Plant() : Tile(ResourceType::PLANT, NO_ARMOR) {}

bool Plant::canFly() { return true; }

bool Plant::canDrive() { return true; }

bool Plant::isPartOfBackground() { return false; }
