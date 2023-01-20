#pragma once

#include "Tile.h"

class Plain : public Tile
{
public:
    explicit Plain(Coordinates coordinates);

    bool canFly() override;
    bool canDrive() override;

    ResourceType getResourceType() const override;
};
