#include "Plain.h"

Plain::Plain() : Tile(ResourceType::PLAIN, NO_ARMOR) {}

bool Plain::canFly() { return true; }

bool Plain::canDrive() { return true; }
