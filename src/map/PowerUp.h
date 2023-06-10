#pragma once

#include "Tile.h"

class PowerUp : public Tile
{
public:
    PowerUp(unsigned int armor, Point point);

    bool canFly() override;
    bool canDrive() override;
};
