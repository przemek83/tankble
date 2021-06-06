#pragma once

#include "tile.h"

class ArmorUp : public Tile
{
public:
    ArmorUp();

    bool canFly() override;
    bool canDrive() override;
};
class SpeedUp : public Tile
{
public:
    SpeedUp();

    bool canFly() override;
    bool canDrive() override;
};
class TankUp : public Tile
{
public:
    TankUp();

    bool canFly() override;
    bool canDrive() override;
};
class LevelUp : public Tile
{
public:
    LevelUp();

    bool canFly() override;
    bool canDrive() override;
};
