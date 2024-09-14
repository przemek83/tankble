#pragma once

#include <src/Display.h>

class FakeDisplay : public Display
{
public:
    int getResourceWidth(
        [[maybe_unused]] ResourceType resourceType) const override
    {
        return 0;
    }
    int getResourceHeight(
        [[maybe_unused]] ResourceType resourceType) const override
    {
        return 0;
    }
};