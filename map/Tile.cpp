#include "Tile.h"

Tile::Tile(ResourceType resourceType, unsigned int armor)
    : armor_(armor), resourceType_(resourceType)
{
}

bool Tile::isPartOfBackground() { return true; }

bool Tile::destroy(unsigned int power)
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
