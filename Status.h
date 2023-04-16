#pragma once

#include "Drawable.h"

class Status : public Drawable
{
public:
    explicit Status(Point point);

    void draw(const Screen& screen) const override;
    Point getCenter() const override;
    ResourceType getResourceType() const override;

private:
    static unsigned int getHeight();
    static unsigned int getWeidth();
};
