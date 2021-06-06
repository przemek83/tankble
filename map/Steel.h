#pragma once

#include "tile.h"

class Steel : public Tile
{
public:
    Steel();

    bool canFly() override;
    bool canDrive() override;
};
