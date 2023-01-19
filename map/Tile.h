#pragma once

#include "../ResourceType.h"

class Tile
{
public:
    Tile(ResourceType resourceType, unsigned int armor);
    virtual ~Tile() = default;

    Tile& operator=(const Tile& other) = delete;
    Tile(const Tile& other) = delete;

    Tile& operator=(Tile&& other) = delete;
    Tile(Tile&& other) = delete;

    virtual bool canFly() = 0;
    virtual bool canDrive() = 0;
    virtual bool isPartOfBackground();

    bool destroy(unsigned int power);

    bool isPowerUp() const;

    ResourceType getResourceType() const;

protected:
    static const unsigned int MAX_ARMOR{999};
    static const unsigned int HIGH_ARMOR{100};
    static const unsigned int MEDIUM_ARMOR{10};
    static const unsigned int LOW_ARMOR{2};
    static const unsigned int NO_ARMOR{0};

private:
    unsigned int armor_;
    ResourceType resourceType_;
};
