#pragma once

#include "ResourceType.h"

class Screen;

class Drawable
{
public:
    Drawable(unsigned int x, unsigned int y);
    virtual ~Drawable() = default;

    Drawable& operator=(const Drawable& other) = delete;
    Drawable(const Drawable& other) = delete;

    Drawable& operator=(Drawable&& other) = default;
    Drawable(Drawable&& other) = default;

    virtual void draw(const Screen& screen) const = 0;
    virtual ResourceType getResourceType() const = 0;

    void setX(unsigned int x);
    void setY(unsigned int y);

    inline unsigned int getX() const { return x_; }
    inline unsigned int getY() const { return y_; }

private:
    unsigned int x_;
    unsigned int y_;
};
