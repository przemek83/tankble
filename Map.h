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
    explicit Map(Player* player);
    ~Map();

    Map& operator=(const Map& other) = delete;
    Map(const Map& other) = delete;

    Map& operator=(Map&& other) = delete;
    Map(Map&& other) = delete;

    ALLEGRO_BITMAP* display();
    bool canDrive(unsigned int j, unsigned int i);
    bool isValid(int, int);
    void addBullet(std::unique_ptr<Bullet> bullet);
    void moveBullet();
    void setPower(Vehicle* vehicle);

    std::vector<Vehicle*> vehicles;

private:
    bool isBulletValid(int x, int y);
    bool canFly(unsigned int j, unsigned int i);
    void destroyItem(unsigned int j, unsigned int i, unsigned int power);
    int isTank(const std::unique_ptr<Bullet>& bullet);
    void displayMaps();
    void displayPowers();
    void displayVehicles();
    void displayBullets();
    void loadMap();
    void drawMapItem(ALLEGRO_BITMAP* element, int x, int y);

    std::vector<std::unique_ptr<Bullet>> bullets_;
    std::vector<std::vector<std::unique_ptr<Tile>>> board_{};
    ALLEGRO_BITMAP* buffer_;
    ALLEGRO_BITMAP* paint_;
    Player* player_;
};
