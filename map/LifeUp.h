#pragma once

#include "PowerUp.h"

class LifeUp : public PowerUp
{
public:
    explicit LifeUp(Coordinates coordinates);

    ResourceType getResourceType() const override;
};
