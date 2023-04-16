#include "Status.h"

#include "Config.h"
#include "Screen.h"

Status::Status(Point point) : Drawable(point) {}

void Status::draw(const Screen& screen) const
{
    const Point center{getCenter()};
    screen.drawText(center.x, center.y, "[Status placeholder]");
}

Point Status::getCenter() const
{
    return {getX() + getWeidth() / 2, getHeight() / 2};
}

ResourceType Status::getResourceType() const
{
    return ResourceType::BACKGROUND;
}

unsigned int Status::getHeight()
{
    return Config::getInstance().getBoardHeight();
}

unsigned int Status::getWeidth()
{
    return Config::getInstance().getSatusWidth();
}
