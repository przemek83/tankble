#pragma once

#include "Tile.h"

class Brick : public Tile
{
public:
    explicit Brick(Coordinates coordinates);

    bool canFly() override;
    bool canDrive() override;

    ResourceType getResourceType() const override;
};
