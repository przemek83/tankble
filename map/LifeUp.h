#pragma once

#include "PowerUp.h"

class LifeUp : public PowerUp
{
public:
    LifeUp(unsigned int x, unsigned int y);

    ResourceType getResourceType() const override;
};
