#pragma once

#include "PowerUp.h"

class ShieldUp : public PowerUp
{
public:
    explicit ShieldUp(Coordinates coordinates);

    ResourceType getResourceType() const override;
};
