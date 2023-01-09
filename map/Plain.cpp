#include "Plain.h"

#include "../Config.h"

Plain::Plain() : Tile(ResourceType::PLAIN, Config::noArmor) {}

bool Plain::canFly() { return true; }

bool Plain::canDrive() { return true; }
