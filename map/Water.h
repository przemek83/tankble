#pragma once

#include "Tile.h"

class Water : public Tile
{
public:
    Water(unsigned int x, unsigned int y);

    bool canFly() override;
    bool canDrive() override;

    ResourceType getResourceType() const override;
};
