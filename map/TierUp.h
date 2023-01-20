#pragma once

#include "PowerUp.h"

class TierUp : public PowerUp
{
public:
    explicit TierUp(Coordinates coordinates);

    ResourceType getResourceType() const override;
};
