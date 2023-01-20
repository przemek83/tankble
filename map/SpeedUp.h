#pragma once

#include "PowerUp.h"

class SpeedUp : public PowerUp
{
public:
    SpeedUp(unsigned int x, unsigned int y);

    ResourceType getResourceType() const override;
};
