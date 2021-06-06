#pragma once

#include "tile.h"

class Plain : public Tile
{
public:
    Plain();

    bool canFly() override;
    bool canDrive() override;
};
