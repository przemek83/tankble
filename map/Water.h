#pragma once

#include "Tile.h"

class Water : public Tile
{
public:
    explicit Water(Coordinates coordinates);

    bool canFly() override;
    bool canDrive() override;

    ResourceType getResourceType() const override;
};
