#include "tile.h"
#include <cstdio>
#include "../config.h"

Tile::~Tile()
{
    al_destroy_bitmap(bmp);
    std::cout << "MapElement " << getId() << " is deleted\n";
}

bool Tile::loadBitmap()
{
    FILE* fp;
    if ((fp = fopen(source, "r")) == NULL)
        return false;
    fclose(fp);
    bmp = al_load_bitmap(source);  //, palette);
    return true;
}

bool Tile::destroy(int power)
{
    armor -= power;
    if (armor <= 0)
        return true;
    return false;
}
ALLEGRO_BITMAP* Tile::display() { return bmp; }

int Tile::getId() { return id; }

int Tile::getArmorUp() { return armorUp; }

int Tile::getLevelUp() { return levelUp; }

int Tile::getSpeedUp() { return speedUp; }

int Tile::getTankUp() { return tankUp; }
