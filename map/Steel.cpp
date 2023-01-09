#include "Steel.h"

Steel::Steel() : Tile(ResourceType::STEEL, HIGH_ARMOR) {}

bool Steel::canFly() { return false; }

bool Steel::canDrive() { return false; }
