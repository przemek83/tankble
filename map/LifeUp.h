#pragma once

#include "PowerUp.h"

class LifeUp : public PowerUp
{
public:
    explicit LifeUp(Point point);

    ResourceType getResourceType() const override;
};
