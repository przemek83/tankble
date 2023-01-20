#pragma once

#include "Tile.h"

class PowerUp : public Tile
{
public:
    PowerUp(unsigned int armor, unsigned int x, unsigned int y);

    bool canFly() override;
    bool canDrive() override;
};
