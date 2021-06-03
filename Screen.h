#pragma once

#include <string>

#include "Resources.h"

struct ALLEGRO_FONT;
struct ALLEGRO_BITMAP;

class Screen final
{
public:
    explicit Screen(Resources resources);
    ~Screen();

    void drawText(unsigned int x, unsigned y, const std::string& text);

    void drawBackground(Resources::Bitmap bitmap) const;

    void drawBitmap(Resources::Bitmap bitmap, unsigned int x,
                    unsigned int y) const;

    void updateSize();

    unsigned int getCenterX() const;

    unsigned int getCenterY() const;

private:
    unsigned int getWidth() const;

    unsigned int getHeight() const;

    std::pair<unsigned int, unsigned int> getCenter() const;

    Resources resources_;

    unsigned int width_;
    unsigned int height_;
    ALLEGRO_FONT* font_;
};
