#include "Base.h"

#include "../Config.h"

Base::Base() : Tile(ResourceType::BASE, Config::mediumArmor) {}

bool Base::canFly() { return false; }

bool Base::canDrive() { return false; }
