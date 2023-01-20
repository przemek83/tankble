#include "Tile.h"

#include "../Config.h"
#include "../Screen.h"

Tile::Tile(unsigned int armor, unsigned int x, unsigned int y)
    : Drawable(x, y), armor_(armor)
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
    const ResourceType type{getResourceType()};
    return type == ResourceType::SHIELD_UP || type == ResourceType::TIER_UP ||
           type == ResourceType::SPEED_UP || type == ResourceType::LIFE_UP;
}

void Tile::draw(const Screen& screen) const
{
    const unsigned int tileSize{Config::elementSize};
    screen.drawScaledBitmap(getResourceType(), getX(), getY(), tileSize);
}
