#pragma once

#include "Tile.h"

class Steel : public Tile
{
public:
    Steel(unsigned int x, unsigned int y);

    bool canFly() override;
    bool canDrive() override;
};
