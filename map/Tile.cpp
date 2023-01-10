#include "Tile.h"

Tile::Tile(ResourceType resourceType, int armor)
    : armor_(armor), resourceType_(resourceType)
{
}

bool Tile::destroy(int power)
{
    armor_ -= power;
    return armor_ <= 0;
}

bool Tile::isPowerUp() const
{
    return resourceType_ == ResourceType::SHIELD_UP ||
           resourceType_ == ResourceType::TIER_UP ||
           resourceType_ == ResourceType::SPEED_UP ||
           resourceType_ == ResourceType::LIFE_UP;
}

ResourceType Tile::getResourceType() const { return resourceType_; }
