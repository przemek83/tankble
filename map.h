#ifndef MAP_H
#define MAP_H

#include <allegro5/allegro.h>
#include "config.h"
#include "map/base.h"
#include "map/bricks.h"
#include "map/bullet.h"
#include "map/dirt.h"
#include "map/ice.h"
#include "map/map_element.h"
#include "map/plants.h"
#include "map/steel.h"
#include "map/water.h"
#include "player.h"
#include "vehicle.h"

class Map
{
private:
    MapElement* board[MAP_SIZE][MAP_SIZE];
    ALLEGRO_BITMAP* buffer;
    ALLEGRO_BITMAP* paint;
    void displayMaps();
    void displayPowers();
    void displayVehicles();
    void displayBullets();
    void loadMap();
    int tab[MAP_SIZE][MAP_SIZE];
    Player* player;

public:
    Map(Player*);
    ~Map();
    ALLEGRO_BITMAP* display();
    bool canDrive(uint, uint);
    bool isValid(int, int);
    bool isBulletValid(int, int);
    bool canFly(uint, uint);
    void destroyItem(uint, uint, uint);
    vector<Vehicle*> vehicles;
    vector<Bullet*> bullets;
    void addBullet(Bullet*);
    void moveBullet();
    int isTank(Bullet*);
    void setPower(Vehicle*);
};

#endif

// end of map.h
