#pragma once

#include "Tile.h"

class Ice : public Tile
{
public:
    explicit Ice(Point point);

    bool canFly() override;
    bool canDrive() override;

    ResourceType getResourceType() const override;
};
