#include "Tile.h"

#include "../Config.h"
#include "../Display.h"

Tile::Tile(int armor, Point point) : Drawable(point), armor_(armor) {}

bool Tile::isPartOfBackground() { return true; }

bool Tile::hit(int power)
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
    return (type == ResourceType::SHIELD_UP) ||
           (type == ResourceType::TIER_UP) ||
           (type == ResourceType::SPEED_UP) || (type == ResourceType::LIFE_UP);
}

void Tile::draw(const Display& display) const
{
    const int tileSize{Config::getInstance().getTileSize()};
    display.drawScaledSquareBitmap(getResourceType(), getX(), getY(), tileSize);
}

Point Tile::getCenter() const
{
    const int middle{Config::getInstance().getTileSize()};
    return {getX() + middle, getY() + middle};
}
