#pragma once

#include "Tile.h"

class Water : public Tile
{
public:
    explicit Water(Point point);

    bool canFly() override;
    bool canDrive() override;

    ResourceType getResourceType() const override;
};
