#pragma once

#include "Tile.h"

class Plain : public Tile
{
public:
    explicit Plain(Point point);

    bool canFly() override;
    bool canDrive() override;

    ResourceType getResourceType() const override;
};
