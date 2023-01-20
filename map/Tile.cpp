#include "Tile.h"

#include "../Config.h"
#include "../Screen.h"

Tile::Tile(ResourceType resourceType, unsigned int armor, unsigned int x,
           unsigned int y)
    : Drawable(x, y), armor_(armor), resourceType_(resourceType)
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

void Tile::draw(const Screen& screen) const
{
    const unsigned int tileSize{Config::elementSize};
    screen.drawScaledBitmap(resourceType_, getX(), getY(), tileSize);
}
