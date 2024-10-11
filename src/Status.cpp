#include "Status.h"

#include <string>

#include "Config.h"
#include "Display.h"
#include "Utils.h"

Status::Status(Point point) : Drawable(point) {}

void Status::update(TankStats newStats, const Display& display)
{
    if ((stats_.attackPower_ != newStats.attackPower_) ||
        (stats_.shield_ != newStats.shield_) ||
        (stats_.lives_ != newStats.lives_) ||
        (stats_.speed_ != newStats.speed_))
    {
        stats_ = newStats;
        draw(display);
    }
}

void Status::draw(const Display& display) const
{
    const int spacer{getHeight() / 5};
    int verticalPosition{spacer};
    display.drawTextWithBackground(getCenter().x_, verticalPosition,
                                   "Lives: " + std::to_string(stats_.lives_));
    verticalPosition += spacer;
    display.drawTextWithBackground(getCenter().x_, verticalPosition,
                                   "Shield: " + std::to_string(stats_.shield_));
    verticalPosition += spacer;
    display.drawTextWithBackground(getCenter().x_, verticalPosition,
                                   "Speed: " + std::to_string(stats_.speed_));
    verticalPosition += spacer;
    display.drawTextWithBackground(
        getCenter().x_, verticalPosition,
        "Attack: " + std::to_string(stats_.attackPower_));
}

Point Status::getCenter() const
{
    return {getX() + utils::getMidpoint(getWeidth()),
            utils::getMidpoint(getHeight())};
}

ResourceType Status::getResourceType() const
{
    return ResourceType::BACKGROUND;
}

int Status::getHeight() { return Config::getInstance().getBoardHeight(); }

int Status::getWeidth() { return Config::getInstance().getSatusWidth(); }
