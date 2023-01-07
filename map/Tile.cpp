#include "Tile.h"

#include <filesystem>

Tile::~Tile()
{
    al_destroy_bitmap(bmp_);
    std::cout << "MapElement " << static_cast<int>(getId()) << " is deleted\n";
}

bool Tile::loadBitmap()
{
    if (!std::filesystem::exists(source_))
        return false;
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
