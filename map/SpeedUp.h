#pragma once

#include "PowerUp.h"

class SpeedUp : public PowerUp
{
public:
    explicit SpeedUp(Coordinates coordinates);

    ResourceType getResourceType() const override;
};
