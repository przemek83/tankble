#pragma once

#include "tile.h"

class Brick : public Tile
{
public:
    Brick();

    bool canFly() override;
    bool canDrive() override;
};
