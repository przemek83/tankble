#pragma once

#include "Drawable.h"
#include "TankStats.h"

class Status : public Drawable
{
public:
    explicit Status(Point point);

    void update(TankStats newStats, const Screen& screen);

    void draw(const Screen& screen) const override;
    Point getCenter() const override;
    ResourceType getResourceType() const override;

private:
    static unsigned int getHeight();
    static unsigned int getWeidth();

    TankStats stats_{};
};
