#pragma once

#include "Tile.h"

class Base : public Tile
{
public:
    Base();

    bool canFly() override;
    bool canDrive() override;
};
