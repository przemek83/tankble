#pragma once

#include "Drawable.h"
#include "TankStats.h"

class Status : public Drawable
{
public:
    explicit Status(Point point);

    void update(TankStats newStats, const Display& display);

    void draw(const Display& display) const override;
    Point getCenter() const override;
    ResourceType getResourceType() const override;

private:
    static int getHeight();
    static int getWeidth();

    TankStats stats_{};
};
