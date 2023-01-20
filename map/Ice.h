#pragma once

#include "Tile.h"

class Ice : public Tile
{
public:
    Ice(unsigned int x, unsigned int y);

    bool canFly() override;
    bool canDrive() override;

    ResourceType getResourceType() const override;
};
