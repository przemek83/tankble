#pragma once

#include "Tile.h"

class Plain : public Tile
{
public:
    Plain();

    bool canFly() override;
    bool canDrive() override;
};
