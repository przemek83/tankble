#pragma once

#include <src/Display.h>

class FakeDisplay : public Display
{
public:
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

private:
    int resourceWidth_;
    int resourceHeight_;
};
