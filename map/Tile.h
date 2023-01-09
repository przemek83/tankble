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

protected:
    static const unsigned int MAX_ARMOR{999};
    static const unsigned int HIGH_ARMOR{100};
    static const unsigned int MEDIUM_ARMOR{10};
    static const unsigned int LOW_ARMOR{2};
    static const unsigned int NO_ARMOR{0};

private:
    int armor_;
    ResourceType resourceType_;
};
