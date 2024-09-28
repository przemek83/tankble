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

    void setX(int x);
    void setY(int y);

    int getX() const { return point_.x_; }
    int getY() const { return point_.y_; }

    void setLocation(Point point);
    Point getLocation() const;

private:
    Point point_;
};
