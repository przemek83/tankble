#include "Resources.h"

#include <filesystem>
#include <fstream>
#include <iostream>

#include <allegro5/allegro.h>

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

std::fstream Resources::getLevel() const
{
    if (!std::filesystem::exists("missions/mission1.dat"))
        exit(1);

    std::fstream stream("missions/mission1.dat", std::fstream::in);
    return stream;
}
