#pragma once

#include "Tile.h"

class Water : public Tile
{
public:
    Water();

    bool canFly() override;
    bool canDrive() override;
};
