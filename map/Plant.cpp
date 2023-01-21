#include "Plant.h"

Plant::Plant(Point point) : Tile(NO_ARMOR, point) {}

bool Plant::canFly() { return true; }

bool Plant::canDrive() { return true; }

bool Plant::isPartOfBackground() { return false; }

ResourceType Plant::getResourceType() const { return ResourceType::PLANT; }
