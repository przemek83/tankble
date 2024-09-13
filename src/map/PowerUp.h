#pragma once

#include "Tile.h"

class PowerUp : public Tile
{
public:
    PowerUp(int armor, Point point);

    bool canFly() override;
    bool canDrive() override;
};
