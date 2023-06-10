#pragma once

#include "PowerUp.h"

class ShieldUp : public PowerUp
{
public:
    explicit ShieldUp(Point point);

    ResourceType getResourceType() const override;
};
