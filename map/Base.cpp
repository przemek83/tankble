#include "Base.h"

Base::Base() : Tile(ResourceType::BASE, MEDIUM_ARMOR) {}

bool Base::canFly() { return false; }

bool Base::canDrive() { return false; }
