#include "Screen.h"

#include "allegro5/allegro_font.h"

Screen::Screen() : font_{al_create_builtin_font()} {}

Screen::~Screen() { al_destroy_font(font_); }

void Screen::drawText(unsigned int x, unsigned y, const std::string& text)
{
    const ALLEGRO_COLOR white{al_map_rgb(255, 255, 255)};
    al_draw_text(font_, white, static_cast<float>(x), static_cast<float>(y),
                 ALLEGRO_ALIGN_CENTER, text.c_str());
}
