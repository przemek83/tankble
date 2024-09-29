#pragma once

#include <string>

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

    virtual bool init() = 0;

    virtual void drawText(int x, int y, const std::string& text) const = 0;

    virtual void drawTextWithBackground(int x, int y,
                                        const std::string& text) const = 0;

    virtual void drawBackground(ResourceType resourceType) const = 0;

    void drawScaledSquareBitmap(ResourceType resourceType, int x, int y,
                                int size) const;

    virtual void drawScaledBitmap(ResourceType resourceType, int x, int y,
                                  int width, int height) const = 0;

    virtual void drawScaledBitmapWithRotation(ResourceType resourceType, int x,
                                              int y, int size,
                                              int degrees) const = 0;

    virtual void clearScreenWithBlack() = 0;

    virtual int getResourceWidth(ResourceType resourceType) const = 0;
    virtual int getResourceHeight(ResourceType resourceType) const = 0;

    virtual void refresh() = 0;

    virtual void showMouse() = 0;

    virtual void hideMouse() = 0;

    virtual void useFullScreenMode() = 0;

    virtual void useWindowedMode() = 0;

private:
    int width_;
    int height_;
};
