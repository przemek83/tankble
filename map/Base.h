#pragma once

#include "Tile.h"

class Base : public Tile
{
public:
    explicit Base(Point point);

    bool canFly() override;
    bool canDrive() override;

    ResourceType getResourceType() const override;
};
