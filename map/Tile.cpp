#include "Tile.h"

#include <cstdio>

#include "../Config.h"

Tile::~Tile()
{
    al_destroy_bitmap(bmp_);
    std::cout << "MapElement " << static_cast<int>(getId()) << " is deleted\n";
}

bool Tile::loadBitmap()
{
    FILE* fp{nullptr};
    if ((fp = fopen(source_, "r")) == nullptr)
        return false;
    fclose(fp);
    bmp_ = al_load_bitmap(source_);  //, palette);
    return true;
}

bool Tile::destroy(int power)
{
    armor_ -= power;
    return armor_ <= 0;
}
ALLEGRO_BITMAP* Tile::display() { return bmp_; }

bool Tile::isPowerUp() const
{
    return id_ == Type::ARMOR_UP || id_ == Type::LEVEL_UP ||
           id_ == Type::SPEED_UP || id_ == Type::TANK_UP;
}

Tile::Type Tile::getId() const { return id_; }
