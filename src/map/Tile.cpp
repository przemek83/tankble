#include "Tile.h"

#include "../Config.h"
#include "../Screen.h"

Tile::Tile(unsigned int armor, Point point)
    : Drawable(point), armor_(armor)
{
}

bool Tile::isPartOfBackground() { return true; }

bool Tile::hit(unsigned int power)
{
    if (power > armor_)
        armor_ = 0;
    else
        armor_ -= power;

    return armor_ == 0;
}

bool Tile::isPowerUp() const
{
    const ResourceType type{getResourceType()};
    return type == ResourceType::SHIELD_UP || type == ResourceType::TIER_UP ||
           type == ResourceType::SPEED_UP || type == ResourceType::LIFE_UP;
}

void Tile::draw(const Screen& screen) const
{
    const unsigned int tileSize{Config::getInstance().getTileSize()};
    screen.drawScaledSquareBitmap(getResourceType(), getX(), getY(), tileSize);
}

Point Tile::getCenter() const
{
    const unsigned int middle{Config::getInstance().getTileSize()};
    return {getX() + middle, getY() + middle};
}
