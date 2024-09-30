#pragma once

#include "Point.h"
#include "ResourceType.h"

class Display;

class Drawable
{
public:
    explicit Drawable(Point point);
    virtual ~Drawable();

    virtual void draw(const Display& display) const = 0;
    virtual ResourceType getResourceType() const = 0;
    virtual Point getCenter() const = 0;

    int getX() const;
    void setX(int x);

    int getY() const;
    void setY(int y);

    void setLocation(Point point);
    Point getLocation() const;

private:
    Point point_;
};
