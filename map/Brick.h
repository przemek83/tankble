#pragma once

#include "Tile.h"

class Brick : public Tile
{
public:
    explicit Brick(Point point);

    bool canFly() override;
    bool canDrive() override;

    ResourceType getResourceType() const override;
};
