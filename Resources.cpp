#include "Resources.h"

#include <allegro5/allegro.h>

Resources::Resources()
{
    bitmaps_.resize(bitmapPaths_.size());

    unsigned int currentBitmap{0};
    for (const auto& path : bitmapPaths_)
        bitmaps_[currentBitmap++] = al_load_bitmap(path.c_str());
}

Resources::~Resources()
{
    for (const auto& bitmap : bitmaps_)
        al_destroy_bitmap(bitmap);
}

ALLEGRO_BITMAP* Resources::getBitmap(Resources::Bitmap bitmap) const
{
    return bitmaps_.at(static_cast<size_t>(bitmap));
}
