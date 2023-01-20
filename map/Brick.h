#pragma once

#include "Tile.h"

class Brick : public Tile
{
public:
    Brick(unsigned int x, unsigned int y);

    bool canFly() override;
    bool canDrive() override;
};
