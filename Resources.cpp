#include "Resources.h"

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
