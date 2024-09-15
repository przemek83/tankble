#include "Status.h"

#include "Config.h"
#include "Screen.h"
#include "Utils.h"

Status::Status(Point point) : Drawable(point) {}

void Status::update(TankStats newStats, const Screen& screen)
{
    if ((stats_.attackPower_ != newStats.attackPower_) ||
        (stats_.shield_ != newStats.shield_) ||
        (stats_.lives_ != newStats.lives_) ||
        (stats_.speed_ != newStats.speed_))
    {
        stats_ = newStats;
        draw(screen);
    }
}

void Status::draw(const Screen& screen) const
{
    const int spacer{getHeight() / 5};
    screen.drawTextWithBackground(getCenter().x_, spacer * 1,
                                  "Lives: " + std::to_string(stats_.lives_));
    screen.drawTextWithBackground(getCenter().x_, spacer * 2,
                                  "Shield: " + std::to_string(stats_.shield_));
    screen.drawTextWithBackground(getCenter().x_, spacer * 3,
                                  "Speed: " + std::to_string(stats_.speed_));
    screen.drawTextWithBackground(
        getCenter().x_, spacer * 4,
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
