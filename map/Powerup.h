#pragma once

#include "Tile.h"

class Powerup : public Tile
{
public:
    Powerup(ResourceType resourceType, int armor);

    bool canFly() override;
    bool canDrive() override;
};
