#include "Powerup.h"

ArmorUp::ArmorUp() : Tile(ResourceType::ARMOR_UP, NO_ARMOR) {}

bool ArmorUp::canFly() { return true; }

bool ArmorUp::canDrive() { return true; }

SpeedUp::SpeedUp() : Tile(ResourceType::SPEED_UP, NO_ARMOR) {}

bool SpeedUp::canFly() { return true; }

bool SpeedUp::canDrive() { return true; }

TankUp::TankUp() : Tile(ResourceType::TANK_UP, NO_ARMOR) {}

bool TankUp::canFly() { return true; }

bool TankUp::canDrive() { return true; }

LevelUp::LevelUp() : Tile(ResourceType::LEVEL_UP, NO_ARMOR) {}

bool LevelUp::canFly() { return true; }

bool LevelUp::canDrive() { return true; }
