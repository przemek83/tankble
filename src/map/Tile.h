#pragma once

#include "../Drawable.h"

class Tile : public Drawable
{
public:
    Tile(int armor, Point point);

    virtual bool canFly() = 0;
    virtual bool canDrive() = 0;

    virtual bool isPartOfBackground();

    bool hit(int power);

    bool isPowerUp() const;

    void draw(const Display& display) const override;
    Point getCenter() const override;

protected:
    static const int MAX_ARMOR{999};
    static const int HIGH_ARMOR{100};
    static const int MEDIUM_ARMOR{10};
    static const int LOW_ARMOR{2};
    static const int NO_ARMOR{0};

private:
    int armor_;
};
