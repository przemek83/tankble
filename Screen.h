#pragma once

#include <string>

class ALLEGRO_FONT;

class Screen final
{
public:
    Screen();
    ~Screen();

    void drawText(unsigned int x, unsigned y, const std::string& text);

private:
    ALLEGRO_FONT* font_;
};
