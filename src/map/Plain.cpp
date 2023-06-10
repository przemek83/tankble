#include "Plain.h"

Plain::Plain(Point point) : Tile(NO_ARMOR, point) {}

bool Plain::canFly() { return true; }

bool Plain::canDrive() { return true; }

ResourceType Plain::getResourceType() const { return ResourceType::PLAIN; }
