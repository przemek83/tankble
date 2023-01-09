#include "Powerup.h"

#include "../Config.h"

ArmorUp::ArmorUp() : Tile(ResourceType::ARMOR_UP, Config::noArmor) {}

bool ArmorUp::canFly() { return true; }

bool ArmorUp::canDrive() { return true; }

SpeedUp::SpeedUp() : Tile(ResourceType::SPEED_UP, Config::noArmor) {}

bool SpeedUp::canFly() { return true; }

bool SpeedUp::canDrive() { return true; }

TankUp::TankUp() : Tile(ResourceType::TANK_UP, Config::noArmor) {}

bool TankUp::canFly() { return true; }

bool TankUp::canDrive() { return true; }

LevelUp::LevelUp() : Tile(ResourceType::LEVEL_UP, Config::noArmor) {}

bool LevelUp::canFly() { return true; }

bool LevelUp::canDrive() { return true; }
