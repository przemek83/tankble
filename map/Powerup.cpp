#include "Powerup.h"

Powerup::Powerup(ResourceType resourceType, int armor)
    : Tile(resourceType, armor)
{
}

bool Powerup::canFly() { return true; }

bool Powerup::canDrive() { return true; }

ShieldUp::ShieldUp() : Powerup(ResourceType::SHIELD_UP, NO_ARMOR) {}

SpeedUp::SpeedUp() : Powerup(ResourceType::SPEED_UP, NO_ARMOR) {}

LifeUp::LifeUp() : Powerup(ResourceType::TANK_UP, NO_ARMOR) {}

TierUp::TierUp() : Powerup(ResourceType::LEVEL_UP, NO_ARMOR) {}
