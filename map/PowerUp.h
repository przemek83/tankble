#pragma once

#include "Tile.h"

class PowerUp : public Tile
{
public:
    PowerUp(unsigned int armor, Coordinates coordinates);

    bool canFly() override;
    bool canDrive() override;
};
