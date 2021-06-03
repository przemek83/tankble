#pragma once

#include <string>

struct ALLEGRO_FONT;
struct ALLEGRO_BITMAP;

class Screen final
{
public:
    Screen();
    ~Screen();

    void drawText(unsigned int x, unsigned y, const std::string& text);

    void drawBackground(ALLEGRO_BITMAP* bitmap) const;

    void drawBitmap(ALLEGRO_BITMAP* bitmap, unsigned int x,
                    unsigned int y) const;

    void updateSize();

    unsigned int getWidth() const;

    unsigned int getHeight() const;

    std::pair<unsigned int, unsigned int> getCenter() const;

    unsigned int getCenterX() const;

    unsigned int getCenterY() const;

private:
    unsigned int width_;
    unsigned int height_;
    ALLEGRO_FONT* font_;
};
