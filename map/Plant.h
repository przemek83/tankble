#pragma once

#include "Tile.h"

class Plant : public Tile
{
public:
    explicit Plant(Coordinates coordinates);

    bool canFly() override;
    bool canDrive() override;
    bool isPartOfBackground() override;

    ResourceType getResourceType() const override;
};
