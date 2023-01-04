#include "Player.h"

#include "Vehicle.h"

Player::Player() { setTanks(0); }

void Player::loadVehicle(Vehicle* v)
{
    setVehicle(v);
    x_ = v->getX();
    y_ = v->getY();
    setLevel(v->getType());
}

void Player::setTanks(int tanks) { ptanks_ = tanks; }

int Player::getLevel()
{
    try
    {
        return getVehicle()->getType();
    }
    catch (...)
    {
        return plevel_;
    }
}

void Player::setLevel(int level) { plevel_ = level; }

int Player::getTanks() { return ptanks_; }

Vehicle* Player::getVehicle()
{
    if (vehicle_ != nullptr)
    {
        return vehicle_;
    }
    if (getTanks() > 0)
    {
        setVehicle(new Vehicle(getLevel(), x_, y_));
        setTanks(getTanks() - 1);
        return vehicle_;
    }
    throw Lose();
}

void Player::setVehicle(Vehicle* v) { vehicle_ = v; }

Vehicle* Player::killVehicle()
{
    // delete vehicle_;
    vehicle_ = nullptr;
    return getVehicle();
}
