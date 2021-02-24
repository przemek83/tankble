#include "tile.h"
#include <cstdio>
#include "../config.h"

Tile::~Tile()
{
    al_destroy_bitmap(this->bmp);
    cout << "MapElement " << this->getId() << " is deleted\n";
}

bool Tile::loadBitmap()
{
    FILE* fp;
    if ((fp = fopen(source, "r")) == NULL)
    {
        return false;
    }
    fclose(fp);
    this->bmp = al_load_bitmap(source);  //, palette);
    return true;
}

bool Tile::canFly() { return this->fly; }

bool Tile::canDrive() { return this->drive; }

bool Tile::destroy(int power)
{
    this->armor -= power;
    if (this->armor <= 0)
        return true;
    return false;
}
ALLEGRO_BITMAP* Tile::display() { return this->bmp; }

int Tile::getId() { return this->id; }

int Tile::getArmorUp() { return this->armorUp; }

int Tile::getLevelUp() { return this->levelUp; }

int Tile::getSpeedUp() { return this->speedUp; }

int Tile::getTankUp() { return this->tankUp; }
