#include "Plain.h"

Plain::Plain(Coordinates coordinates) : Tile(NO_ARMOR, coordinates) {}

bool Plain::canFly() { return true; }

bool Plain::canDrive() { return true; }

ResourceType Plain::getResourceType() const { return ResourceType::PLAIN; }
