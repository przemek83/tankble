#pragma once

#include <map>
#include <string>

#include "Drawable.h"
#include "UserChoice.h"

class MenuItem : public Drawable
{
public:
    MenuItem(Point point, UserChoice userChoice);

    void initDimensions(const Screen& screen);

    void draw(const Screen& screen) const override;
    ResourceType getResourceType() const override;
    Point getCenter() const override;

    void setSelected(bool selected);

    UserChoice getUserChoice() const;

private:
    std::map<UserChoice, std::string> labels_{
        {UserChoice::LEVEL_MENU, "NEW GAME"},
        {UserChoice::OPTIONS_MENU, "OPTIONS"},
        {UserChoice::EXIT, "EXIT"},
        {UserChoice::LEVEL_1, "LEVEL 1"},
        {UserChoice::LEVEL_2, "LEVEL 2"},
        {UserChoice::LEVEL_3, "LEVEL 3"},
        {UserChoice::LEVEL_4, "LEVEL 4"},
        {UserChoice::BACK, "BACK"},
        {UserChoice::FULLSCREEN, "FULL SCREEN"},
        {UserChoice::WINDOWED, "WINDOWED"},
        {UserChoice::BACK, "BACK"}};

    UserChoice userChoice_;

    int width_{0};
    int height_{0};
    ResourceType resourceType_{ResourceType::MENU_ITEM};
};
