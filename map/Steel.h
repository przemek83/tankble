#pragma once

#include "Tile.h"

class Steel : public Tile
{
public:
    Steel();

    bool canFly() override;
    bool canDrive() override;
};
