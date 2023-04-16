#include "Status.h"

#include "Config.h"
#include "Screen.h"

Status::Status(Point point) : Drawable(point) {}

void Status::update(TankStats newStats, const Screen& screen)
{
    if (stats_.attackPower != newStats.attackPower ||
        stats_.shield != newStats.shield || stats_.lives != newStats.lives ||
        stats_.speed != newStats.speed)
    {
        stats_ = newStats;
        draw(screen);
    }
}

void Status::draw(const Screen& screen) const
{
    const unsigned int spacer{getHeight() / 5};
    screen.drawTextWithBackground(getCenter().x, spacer * 1,
                                  "Lives: " + std::to_string(stats_.lives));
    screen.drawTextWithBackground(getCenter().x, spacer * 2,
                                  "Shield: " + std::to_string(stats_.shield));
    screen.drawTextWithBackground(getCenter().x, spacer * 3,
                                  "Speed: " + std::to_string(stats_.speed));
    screen.drawTextWithBackground(
        getCenter().x, spacer * 4,
        "Attack: " + std::to_string(stats_.attackPower));
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
