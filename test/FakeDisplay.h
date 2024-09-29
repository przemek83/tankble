#pragma once

#include <src/Display.h>

class FakeDisplay : public Display
{
public:
    bool init() override { return true; };

    void drawText([[maybe_unused]] int x, [[maybe_unused]] int y,
                  [[maybe_unused]] const std::string& text) const override {};

    void drawTextWithBackground(
        [[maybe_unused]] int x, [[maybe_unused]] int y,
        [[maybe_unused]] const std::string& text) const override {};

    void drawBackground(
        [[maybe_unused]] ResourceType resourceType) const override {};

    void drawScaledBitmap([[maybe_unused]] ResourceType resourceType,
                          [[maybe_unused]] int x, [[maybe_unused]] int y,
                          [[maybe_unused]] int width,
                          [[maybe_unused]] int height) const override {};

    void drawScaledBitmapWithRotation(
        [[maybe_unused]] ResourceType resourceType, [[maybe_unused]] int x,
        [[maybe_unused]] int y, [[maybe_unused]] int size,
        [[maybe_unused]] int degrees) const override {};

    void clearScreenWithBlack() override {};

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

    void refresh() override {};

    void showMouse() override {};

    void hideMouse() override {};

    void useFullScreenMode() override {};

    void useWindowedMode() override {};

private:
    int resourceWidth_;
    int resourceHeight_;
};
