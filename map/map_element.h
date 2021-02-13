#ifndef MAP_ELEMENT_H
#define MAP_ELEMENT_H

#include <allegro5/allegro.h>

class MapElement
{
protected:
    bool fly;
    bool drive;
    int armor;
    ALLEGRO_BITMAP* bmp;
    const char* source;
    virtual bool loadBitmap();
    int id;
    int armorUp;
    int levelUp;
    int speedUp;
    int tankUp;

public:
    virtual bool canFly();
    virtual bool canDrive();
    virtual bool destroy(int);
    virtual ALLEGRO_BITMAP* display();  // return bitmap 30x30
    virtual ~MapElement();
    virtual int getId();
    int getArmorUp();
    int getLevelUp();
    int getSpeedUp();
    int getTankUp();
};

#endif

// end of map_element.h
