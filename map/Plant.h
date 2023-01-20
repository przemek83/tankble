#pragma once

#include "Tile.h"

class Plant : public Tile
{
public:
    Plant(unsigned int x, unsigned int y);

    bool canFly() override;
    bool canDrive() override;
    bool isPartOfBackground() override;
};
