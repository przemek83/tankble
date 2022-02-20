#pragma once

#include <string>
#include <vector>

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

    enum class Bitmap : unsigned char
    {
        BACKGROUND = 0,
        MENU_ITEM,
        MENU_ITME_SELECTED
    };

    [[nodiscard]] ALLEGRO_BITMAP* getBitmap(Bitmap bitmap) const;

private:
    std::vector<std::string> bitmapPaths_{"image/menu/background.bmp",
                                          "image/menu/item.tga",
                                          "image/menu/item_select.tga"};

    std::vector<ALLEGRO_BITMAP*> bitmaps_;
};
