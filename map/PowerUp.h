#pragma once

#include "Tile.h"

class PowerUp : public Tile
{
public:
    PowerUp(ResourceType resourceType, int armor);

    bool canFly() override;
    bool canDrive() override;
};
