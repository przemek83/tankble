#pragma once

#include "PowerUp.h"

class SpeedUp : public PowerUp
{
public:
    explicit SpeedUp(Point point);

    ResourceType getResourceType() const override;
};
