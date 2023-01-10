#pragma once

#include "Tile.h"

class Powerup : public Tile
{
public:
    Powerup(ResourceType resourceType, int armor);

    bool canFly() override;
    bool canDrive() override;
};

class ArmorUp : public Powerup
{
public:
    ArmorUp();
};
class SpeedUp : public Powerup
{
public:
    SpeedUp();
};
class LifeUp : public Powerup
{
public:
    LifeUp();
};
class TierUp : public Powerup
{
public:
    TierUp();
};
