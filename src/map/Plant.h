#pragma once

#include "Tile.h"

class Plant : public Tile
{
public:
    explicit Plant(Point point);

    bool canFly() override;
    bool canDrive() override;
    bool isPartOfBackground() override;

    ResourceType getResourceType() const override;
};
