#include "Resources.h"

#include <filesystem>
#include <fstream>
#include <iostream>

#include <allegro5/allegro.h>

Resources::~Resources()
{
    for (const auto& [_, bitmap] : bitmaps_)
        ::al_destroy_bitmap(bitmap);
}

ALLEGRO_BITMAP* Resources::getBitmap(ResourceType resourceType) const
{
    if (bitmaps_.empty())
        for (const auto& [resType, path] : resourcePaths_)
            bitmaps_[resType] = ::al_load_bitmap(path.c_str());
    return bitmaps_.at(resourceType);
}

std::pair<bool, std::fstream> Resources::getLevel(Level level)
{
    const std::unordered_map<Level, std::string> levels{
        {Level::LEVEL_1, "levels/level1.dat"},
        {Level::LEVEL_2, "levels/level2.dat"},
        {Level::LEVEL_3, "levels/level3.dat"},
        {Level::LEVEL_4, "levels/level4.dat"}};

    const std::string& levelName{levels.at(level)};
    if (!std::filesystem::exists(levelName))
    {
        std::cerr << "Cannot open level file: " << levelName << "\n";
        return {false, std::fstream{}};
    }

    std::fstream stream(levelName, std::fstream::in);
    return {true, std::move(stream)};
}
