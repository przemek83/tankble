#pragma once

#include "PowerUp.h"

class TierUp : public PowerUp
{
public:
    explicit TierUp(Point point);

    ResourceType getResourceType() const override;
};
