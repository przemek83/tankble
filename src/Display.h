#pragma once

#include "ResourceType.h"

class Display
{
public:
    Display();

    virtual ~Display() = default;

    int getCenterX() const;
    int getCenterY() const;

    int getWidth() const;
    void setWidth(int width);
    int getHeight() const;
    void setHeight(int height);

    virtual int getResourceWidth(ResourceType resourceType) const = 0;
    virtual int getResourceHeight(ResourceType resourceType) const = 0;

private:
    int width_;
    int height_;
};