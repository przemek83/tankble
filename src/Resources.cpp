#include "Resources.h"

#include <filesystem>
#include <fstream>
#include <iostream>

#include <allegro5/allegro.h>

const std::unordered_map<Level, std::string> Resources::levels_{
    {Level::LEVEL_1, "levels/level1.dat"},
    {Level::LEVEL_2, "levels/level2.dat"},
    {Level::LEVEL_3, "levels/level3.dat"},
    {Level::LEVEL_4, "levels/level4.dat"}};

Resources::Resources()
{
    for (const auto& [resourceType, path] : resourcePaths_)
        bitmaps_[resourceType] = al_load_bitmap(path.c_str());
}

Resources::~Resources()
{
    for (const auto& [_, bitmap] : bitmaps_)
        al_destroy_bitmap(bitmap);
}

ALLEGRO_BITMAP* Resources::getBitmap(ResourceType resourceType) const
{
    return bitmaps_.at(resourceType);
}

std::fstream Resources::getLevel(Level level)
{
    const std::string& levelName{levels_.at(level)};
    if (!std::filesystem::exists(levelName))
        exit(1);

    std::fstream stream(levelName, std::fstream::in);
    return stream;
}
