#pragma once

#include "../ResourceType.h"

class Tile
{
public:
    Tile(ResourceType resourceType, int armor);
    virtual ~Tile() = default;

    virtual bool canFly() = 0;
    virtual bool canDrive() = 0;
    virtual bool destroy(int);

    bool isPowerUp() const;

    ResourceType getResourceType() const;

private:
    int armor_;
    ResourceType resourceType_;
};
