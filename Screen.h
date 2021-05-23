#pragma once

#include <string>

class ALLEGRO_FONT;

class Screen final
{
public:
    Screen();
    ~Screen();

    void drawText(unsigned int x, unsigned y, const std::string& text);

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
