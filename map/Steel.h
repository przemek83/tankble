#pragma once

#include "Tile.h"

class Steel : public Tile
{
public:
    explicit Steel(Coordinates coordinates);

    bool canFly() override;
    bool canDrive() override;

    ResourceType getResourceType() const override;
};
