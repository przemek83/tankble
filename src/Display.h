#pragma once

#include "Config.h"

class Display
{
public:
    Display()
        : width_(Config::getInstance().getBoardWidth() +
                 Config::getInstance().getSatusWidth()),
          height_(Config::getInstance().getBoardHeight())
    {
    }

    virtual ~Display() = default;

    int getCenterX() const { return width_ / 2; }
    int getCenterY() const { return height_ / 2; }

    int getWidth() const { return width_; }
    void setWidth(int width) { width_ = width; }
    int getHeight() const { return height_; }
    void setHeight(int height) { height_ = height; }

private:
    int width_;
    int height_;
};