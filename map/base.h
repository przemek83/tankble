#pragma once

#include "tile.h"

class Base : public Tile
{
public:
    Base();

    bool canFly() override;
    bool canDrive() override;
};
