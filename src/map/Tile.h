#pragma once

#include "../Drawable.h"

class Tile : public Drawable
{
public:
    Tile(unsigned int armor, Point point);

    virtual bool canFly() = 0;
    virtual bool canDrive() = 0;

    virtual bool isPartOfBackground();

    bool hit(unsigned int power);

    bool isPowerUp() const;

    void draw(const Screen& screen) const override;
    Point getCenter() const override;

protected:
    static const unsigned int MAX_ARMOR{999};
    static const unsigned int HIGH_ARMOR{100};
    static const unsigned int MEDIUM_ARMOR{10};
    static const unsigned int LOW_ARMOR{2};
    static const unsigned int NO_ARMOR{0};

private:
    unsigned int armor_;
};
