#include "Plant.h"

Plant::Plant(Coordinates coordinates) : Tile(NO_ARMOR, coordinates) {}

bool Plant::canFly() { return true; }

bool Plant::canDrive() { return true; }

bool Plant::isPartOfBackground() { return false; }

ResourceType Plant::getResourceType() const { return ResourceType::PLANT; }
