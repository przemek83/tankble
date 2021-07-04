#pragma once

#include <memory>

#include <allegro5/allegro.h>
#include "Config.h"
#include "Player.h"
#include "Vehicle.h"
#include "map/Base.h"
#include "map/Brick.h"
#include "map/Bullet.h"
#include "map/Ice.h"
#include "map/Plain.h"
#include "map/Plant.h"
#include "map/Steel.h"
#include "map/Tile.h"
#include "map/Water.h"

class Map
{
public:
    explicit Map(Player*);
    ~Map();

    Map& operator=(const Map& other) = delete;
    Map(const Map& other) = delete;

    Map& operator=(Map&& other) = delete;
    Map(Map&& other) = delete;

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

    std::vector<std::vector<std::unique_ptr<Tile>>> board_{};

    ALLEGRO_BITMAP* buffer_;
    ALLEGRO_BITMAP* paint_;
    void displayMaps();
    void displayPowers();
    void displayVehicles();
    void displayBullets();
    void loadMap();
    void drawMapItem(ALLEGRO_BITMAP* element, int x, int y);
    Player* player_;
};
