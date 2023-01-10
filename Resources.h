#pragma once

#include <string>
#include <unordered_map>

#include "ResourceType.h"

struct ALLEGRO_BITMAP;

class Resources final
{
public:
    Resources();
    ~Resources();

    Resources& operator=(const Resources& other) = delete;
    Resources(const Resources& other) = delete;

    Resources& operator=(Resources&& other) = default;
    Resources(Resources&& other) = default;

    ALLEGRO_BITMAP* getBitmap(ResourceType resourceType) const;

private:
    std::unordered_map<ResourceType, std::string> resourcePaths_{
        {ResourceType::BACKGROUND, "image/menu/background.bmp"},
        {ResourceType::MENU_ITEM, "image/menu/item.tga"},
        {ResourceType::MENU_ITME_SELECTED, "image/menu/item_select.tga"},
        {ResourceType::PLAIN, "image/board/plain.tga"},
        {ResourceType::BRICK, "image/board/brick.tga"},
        {ResourceType::WATER, "image/board/water.tga"},
        {ResourceType::PLANT, "image/board/plant.tga"},
        {ResourceType::ICE, "image/board/ice.tga"},
        {ResourceType::STEEL, "image/board/steel.tga"},
        {ResourceType::BASE, "image/board/base.tga"},
        {ResourceType::SHIELD_UP, "image/board/shield_up.tga"},
        {ResourceType::SPEED_UP, "image/board/speed_up.tga"},
        {ResourceType::LIFE_UP, "image/board/life_up.tga"},
        {ResourceType::TIER_UP, "image/board/tier_up.tga"}};

    std::unordered_map<ResourceType, ALLEGRO_BITMAP*> bitmaps_;
};
