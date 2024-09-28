#pragma once

#include <map>
#include <string>

#include "Drawable.h"
#include "UserChoice.h"

class Display;

class MenuItem : public Drawable
{
public:
    explicit MenuItem(UserChoice userChoice);

    void init(const Display& display, int position, int count);

    void draw(const Display& display) const override;
    ResourceType getResourceType() const override;
    Point getCenter() const override;

    void setSelected(bool selected);

    UserChoice getUserChoice() const;

    int getWidth() const;
    int getHeight() const;

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
