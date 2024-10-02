#include "MenuItem.h"

#include <algorithm>

#include "Display.h"
#include "ResourceType.h"
#include "Utils.h"

MenuItem::MenuItem(UserChoice userChoice)
    : Drawable({}), userChoice_{userChoice}
{
}

void MenuItem::draw(const Display& display) const
{
    display.drawScaledBitmap(resourceType_, getX(), getY(), width_, height_);
    display.drawText(display.getCenterX(), getY() + getCenter().y_,
                     labels_.at(userChoice_));
}

ResourceType MenuItem::getResourceType() const { return resourceType_; }

Point MenuItem::getCenter() const
{
    return {utils::getMidpoint(width_), utils::getMidpoint(height_)};
}

void MenuItem::setSelected(bool selected)
{
    if (selected)
        resourceType_ = ResourceType::MENU_ITEM_SELECTED;
    else
        resourceType_ = ResourceType::MENU_ITEM;
}

void MenuItem::init(const Display& display, int position, int count)
{
    width_ = std::max(display.getWidth() / 3,
                      display.getResourceWidth(ResourceType::MENU_ITEM));
    height_ = std::max(display.getHeight() / 10,
                       display.getResourceHeight(ResourceType::MENU_ITEM));

    setX(display.getCenterX() - utils::getMidpoint(width_));

    const int locationOfFirstItem{display.getCenterY() -
                                  utils::getMidpoint(count * height_)};
    setY(locationOfFirstItem + (height_ * position));
}

UserChoice MenuItem::getUserChoice() const { return userChoice_; }

int MenuItem::getWidth() const { return width_; }
int MenuItem::getHeight() const { return height_; }
