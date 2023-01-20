#pragma once

#include "Tile.h"

class Plain : public Tile
{
public:
    Plain(unsigned int x, unsigned int y);

    bool canFly() override;
    bool canDrive() override;

    ResourceType getResourceType() const override;
};
