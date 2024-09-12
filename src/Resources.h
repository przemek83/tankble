#pragma once

#include <string>
#include <unordered_map>

#include "Level.h"
#include "ResourceType.h"

struct ALLEGRO_BITMAP;

class Resources
{
public:
    Resources();
    ~Resources();

    Resources& operator=(const Resources& other) = delete;
    Resources(const Resources& other) = delete;

    Resources& operator=(Resources&& other) = default;
    Resources(Resources&& other) = default;

    ALLEGRO_BITMAP* getBitmap(ResourceType resourceType) const;

    static std::pair<bool, std::fstream> getLevel(Level level);

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
        {ResourceType::TIER_UP, "image/board/tier_up.tga"},
        {ResourceType::BULLET, "image/board/bullet.tga"},
        {ResourceType::PLAYER_TANK_TIER_1, "image/board/tank_tier1.tga"},
        {ResourceType::PLAYER_TANK_TIER_2, "image/board/tank_tier2.tga"},
        {ResourceType::PLAYER_TANK_TIER_3, "image/board/tank_tier3.tga"},
        {ResourceType::PLAYER_TANK_TIER_4, "image/board/tank_tier4.tga"},
        {ResourceType::ENEMY_TANK_TIER_1, "image/board/tank_tier1_enemy.tga"},
        {ResourceType::ENEMY_TANK_TIER_2, "image/board/tank_tier2_enemy.tga"},
        {ResourceType::ENEMY_TANK_TIER_3, "image/board/tank_tier3_enemy.tga"},
        {ResourceType::ENEMY_TANK_TIER_4, "image/board/tank_tier4_enemy.tga"}};

    std::unordered_map<ResourceType, ALLEGRO_BITMAP*> bitmaps_;
};
