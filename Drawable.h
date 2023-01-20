#pragma once

#include "Coordinates.h"
#include "ResourceType.h"

class Screen;

class Drawable
{
public:
    explicit Drawable(Coordinates coordinates);
    virtual ~Drawable() = default;

    Drawable& operator=(const Drawable& other) = delete;
    Drawable(const Drawable& other) = delete;

    Drawable& operator=(Drawable&& other) = default;
    Drawable(Drawable&& other) = default;

    virtual void draw(const Screen& screen) const = 0;
    virtual ResourceType getResourceType() const = 0;

    void setX(unsigned int x);
    void setY(unsigned int y);

    inline unsigned int getX() const { return coordinates_.x; }
    inline unsigned int getY() const { return coordinates_.y; }

private:
    Coordinates coordinates_;
};
