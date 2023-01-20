#include "Plain.h"

Plain::Plain(unsigned int x, unsigned int y) : Tile(NO_ARMOR, x, y) {}

bool Plain::canFly() { return true; }

bool Plain::canDrive() { return true; }

ResourceType Plain::getResourceType() const { return ResourceType::PLAIN; }
