#include "map_element.h"
#include <cstdio>
#include "../config.h"

MapElement::~MapElement()
{
    al_destroy_bitmap(this->bmp);
    cout << "MapElement " << this->getId() << " is deleted\n";
}

bool MapElement::loadBitmap()
{
    // PALETTE palette;
    FILE* fp;
    if ((fp = fopen(source, "r")) == NULL)
    {
        return false;
    }
    fclose(fp);
    this->bmp = al_load_bitmap(source);  //, palette);
    return true;
}

bool MapElement::canFly() { return this->fly; }

bool MapElement::canDrive() { return this->drive; }

bool MapElement::destroy(int power)
{
    this->armor -= power;
    if (this->armor <= 0)
        return true;
    return false;
}
ALLEGRO_BITMAP* MapElement::display() { return this->bmp; }

int MapElement::getId() { return this->id; }

int MapElement::getArmorUp() { return this->armorUp; }

int MapElement::getLevelUp() { return this->levelUp; }

int MapElement::getSpeedUp() { return this->speedUp; }

int MapElement::getTankUp() { return this->tankUp; }
