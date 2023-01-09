#include "Water.h"

Water::Water() : Tile(ResourceType::WATER, NO_ARMOR) {}

bool Water::canFly() { return true; }

bool Water::canDrive() { return true; }
