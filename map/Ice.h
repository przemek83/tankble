#pragma once

#include "tile.h"

class Ice : public Tile
{
public:
    Ice();

    bool canFly() override;
    bool canDrive() override;
};
