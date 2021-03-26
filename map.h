#pragma once

#include <allegro5/allegro.h>
#include "config.h"
#include "map/base.h"
#include "map/brick.h"
#include "map/bullet.h"
#include "map/ice.h"
#include "map/plain.h"
#include "map/plant.h"
#include "map/steel.h"
#include "map/tile.h"
#include "map/water.h"
#include "player.h"
#include "vehicle.h"

class Map
{
public:
    explicit Map(Player*);
    ~Map();
    ALLEGRO_BITMAP* display();
    bool canDrive(unsigned int j, unsigned int i);
    bool isValid(int, int);
    std::vector<Vehicle*> vehicles;
    void addBullet(Bullet*);
    void moveBullet();
    void setPower(Vehicle*);

private:
    bool isBulletValid(int, int);
    bool canFly(unsigned int j, unsigned int i);
    void destroyItem(unsigned int j, unsigned int i, unsigned int power);
    std::vector<Bullet*> bullets_;
    int isTank(Bullet*);

    Tile* board_[MAP_SIZE][MAP_SIZE];
    ALLEGRO_BITMAP* buffer_;
    ALLEGRO_BITMAP* paint_;
    void displayMaps();
    void displayPowers();
    void displayVehicles();
    void displayBullets();
    void loadMap();
    void drawMapItem(ALLEGRO_BITMAP* element, int x, int y);
    int tab_[MAP_SIZE][MAP_SIZE];
    Player* player_;
};
