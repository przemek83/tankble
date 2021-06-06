#include "Tile.h"

#include <cstdio>

#include "../Config.h"

Tile::~Tile()
{
    al_destroy_bitmap(bmp);
    std::cout << "MapElement " << getId() << " is deleted\n";
}

bool Tile::loadBitmap()
{
    FILE* fp{nullptr};
    if ((fp = fopen(source, "r")) == nullptr)
        return false;
    fclose(fp);
    bmp = al_load_bitmap(source);  //, palette);
    return true;
}

bool Tile::destroy(int power)
{
    armor -= power;
    return armor <= 0;
}
ALLEGRO_BITMAP* Tile::display() { return bmp; }

int Tile::getId() { return id; }

int Tile::getArmorUp() const { return armorUp; }

int Tile::getLevelUp() const { return levelUp; }

int Tile::getSpeedUp() const { return speedUp; }

int Tile::getTankUp() const { return tankUp; }
