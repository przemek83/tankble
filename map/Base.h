#pragma once

#include "Tile.h"

class Base : public Tile
{
public:
    Base(unsigned int x, unsigned int y);

    bool canFly() override;
    bool canDrive() override;

    ResourceType getResourceType() const override;
};
