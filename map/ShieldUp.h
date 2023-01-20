#pragma once

#include "PowerUp.h"

class ShieldUp : public PowerUp
{
public:
    ShieldUp(unsigned int x, unsigned int y);

    ResourceType getResourceType() const override;
};
