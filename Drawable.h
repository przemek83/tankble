#pragma once

class Screen;

class Drawable
{
public:
    Drawable() = default;
    virtual ~Drawable() = default;

    Drawable& operator=(const Drawable& other) = delete;
    Drawable(const Drawable& other) = delete;

    Drawable& operator=(Drawable&& other) = default;
    Drawable(Drawable&& other) = default;

    virtual void draw(Screen& screen) = 0;
};
