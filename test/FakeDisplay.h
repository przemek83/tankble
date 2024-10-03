#pragma once

#include <vector>

#include <src/Display.h>

class FakeDisplay : public Display
{
public:
    struct ChangedArea
    {
        ResourceType type_;
        int x_;
        int y_;
    };

    struct DrawnText
    {
        int x_;
        int y_;
        std::string text_;
    };

    bool init() override { return true; };

    void drawText([[maybe_unused]] int x, [[maybe_unused]] int y,
                  [[maybe_unused]] const std::string& text) const override {};

    void drawTextWithBackground(
        [[maybe_unused]] int x, [[maybe_unused]] int y,
        [[maybe_unused]] const std::string& text) const override
    {
        drawnTexts_.push_back({x, y, text});
    };

    void drawBackground(
        [[maybe_unused]] ResourceType resourceType) const override {};

    void drawScaledBitmap([[maybe_unused]] ResourceType resourceType,
                          [[maybe_unused]] int x, [[maybe_unused]] int y,
                          [[maybe_unused]] int width,
                          [[maybe_unused]] int height) const override
    {
        changedAreas_.push_back({resourceType, x, y});
    };

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

    std::vector<ChangedArea> getChangedAreas() const { return changedAreas_; }

    void resetChangedAreas() { changedAreas_.clear(); }

    std::vector<DrawnText> getDrawnTexts() const { return drawnTexts_; }

    void resetDrawnTexts() { drawnTexts_.clear(); }

private:
    int resourceWidth_{0};
    int resourceHeight_{0};

    mutable std::vector<ChangedArea> changedAreas_;

    mutable std::vector<DrawnText> drawnTexts_;
};
