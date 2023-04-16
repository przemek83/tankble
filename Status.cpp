#include "Status.h"

#include "Config.h"
#include "Screen.h"

Status::Status(Point point) : Drawable(point) {}

void Status::draw(const Screen& screen) const
{
    screen.drawText(Config::getInstance().getBoardWidth() +
                        Config::getInstance().getSatusWidth() / 2,
                    Config::getInstance().getBoardHeight() / 2,
                    "[Status placeholder]");
}

Point Status::getCenter() const
{
    const Config& config{Config::getInstance()};
    return {config.getBoardWidth() + config.getSatusWidth() / 2,
            config.getBoardWidth() / 2};
}

ResourceType Status::getResourceType() const
{
    return ResourceType::BACKGROUND;
}
