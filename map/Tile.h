#pragma once

#include "../Drawable.h"

class Tile : public Drawable
{
public:
    Tile(unsigned int armor, Coordinates coordinates);

    virtual bool canFly() = 0;
    virtual bool canDrive() = 0;

    virtual bool isPartOfBackground();

    bool destroy(unsigned int power);

    bool isPowerUp() const;

    void draw(const Screen& screen) const override;

protected:
    static const unsigned int MAX_ARMOR{999};
    static const unsigned int HIGH_ARMOR{100};
    static const unsigned int MEDIUM_ARMOR{10};
    static const unsigned int LOW_ARMOR{2};
    static const unsigned int NO_ARMOR{0};

private:
    unsigned int armor_;
};
