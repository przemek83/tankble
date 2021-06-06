#pragma once

#include "tile.h"

class Water : public Tile
{
public:
    Water();

    bool canFly() override;
    bool canDrive() override;
};
