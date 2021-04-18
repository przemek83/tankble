#pragma once
#include "tile.h"

class Plant : public Tile
{
public:
    Plant();

    bool canFly() override;
    bool canDrive() override;
};
