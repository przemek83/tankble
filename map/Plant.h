#pragma once

#include "Tile.h"

class Plant : public Tile
{
public:
    Plant();

    bool canFly() override;
    bool canDrive() override;
    bool isPartOfBackground() override;
};
