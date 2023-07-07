#pragma once

#include "Point.h"
#include "ResourceType.h"

class Screen;

class Drawable
{
public:
    explicit Drawable(Point point);
    virtual ~Drawable();

    Drawable& operator=(const Drawable& other) = delete;
    Drawable(const Drawable& other) = delete;

    Drawable& operator=(Drawable&& other) = default;
    Drawable(Drawable&& other) = default;

    virtual void draw(const Screen& screen) const = 0;
    virtual ResourceType getResourceType() const = 0;
    virtual Point getCenter() const = 0;

    void setX(unsigned int x);
    void setY(unsigned int y);

    inline unsigned int getX() const { return point_.x; }
    inline unsigned int getY() const { return point_.y; }

    void setLocation(Point point);
    Point getLocation() const;

private:
    Point point_;
};
