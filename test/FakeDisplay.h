#pragma once

#include <src/Display.h>

class FakeDisplay : public Display
{
public:
    void drawText(int x, int y, const std::string& text) const override {};

    void drawTextWithBackground(int x, int y,
                                const std::string& text) const override {};

    void drawBackground(ResourceType resourceType) const override {};

    void drawScaledBitmap(ResourceType resourceType, int x, int y, int width,
                          int height) const override {};

    void drawScaledBitmapWithRotation(ResourceType resourceType, int x, int y,
                                      int size, int degrees) const override {};

    int getResourceWidth(
        [[maybe_unused]] ResourceType resourceType) const override
    {
        return resourceWidth_;
    }
    int getResourceHeight(
        [[maybe_unused]] ResourceType resourceType) const override
    {
        return resourceHeight_;
    }

    void setResourceWidth(int width) { resourceWidth_ = width; }

    void setResourceHeight(int height) { resourceHeight_ = height; }

    void useFullScreenMode() override {};

    void useWindowedMode() override {};

private:
    int resourceWidth_;
    int resourceHeight_;
};
