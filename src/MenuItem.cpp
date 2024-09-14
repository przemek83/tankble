#include "MenuItem.h"

#include <algorithm>

#include "ResourceType.h"
#include "Screen.h"

MenuItem::MenuItem(UserChoice userChoice)
    : Drawable({}), userChoice_{userChoice}
{
}

void MenuItem::draw(const Screen& screen) const
{
    screen.drawScaledBitmap(resourceType_, getX(), getY(), width_, height_);
    screen.drawText(screen.getCenterX(), getY() + getCenter().y_,
                    labels_.at(userChoice_));
}

ResourceType MenuItem::getResourceType() const { return resourceType_; }

Point MenuItem::getCenter() const { return {width_ / 2, height_ / 2}; }

void MenuItem::setSelected(bool selected)
{
    if (selected)
        resourceType_ = ResourceType::MENU_ITEM_SELECTED;
    else
        resourceType_ = ResourceType::MENU_ITEM;
}

void MenuItem::init(const Screen& screen, int position, int count)
{
    width_ = std::max(screen.getWidth() / 3,
                      screen.getResourceWidth(ResourceType::MENU_ITEM));
    height_ = std::max(screen.getHeight() / 10,
                       screen.getResourceHeight(ResourceType::MENU_ITEM));

    setX(screen.getCenterX() - width_ / 2);

    const int locationOfFirstItem{screen.getCenterY() - (count * height_ / 2)};
    setY(locationOfFirstItem + (height_ * position));
}

UserChoice MenuItem::getUserChoice() const { return userChoice_; }

int MenuItem::getWidth() const { return width_; }
int MenuItem::getHeight() const { return height_; }
