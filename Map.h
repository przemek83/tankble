#pragma once

#include <memory>
#include <vector>

class Vehicle;
class Bullet;
class Tile;
struct ALLEGRO_BITMAP;

class Map
{
public:
    Map();
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

    const std::vector<Vehicle*>& getVehicles() const;

    bool isPlayerDestroyed() const;

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

    std::vector<Vehicle*> vehicles_;
    std::vector<std::unique_ptr<Bullet>> bullets_;
    std::vector<std::vector<std::unique_ptr<Tile>>> board_{};
    ALLEGRO_BITMAP* buffer_;
    ALLEGRO_BITMAP* paint_;

    bool playerDestroyed_{false};
};
