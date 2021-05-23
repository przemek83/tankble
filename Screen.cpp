#include "Screen.h"

#include "allegro5/allegro_font.h"

#include "config.h"

Screen::Screen()
    : width_(Config::width),
      height_(Config::height),
      font_{al_create_builtin_font()}
{
}

Screen::~Screen() { al_destroy_font(font_); }

void Screen::drawText(unsigned int x, unsigned y, const std::string& text)
{
    const ALLEGRO_COLOR white{al_map_rgb(255, 255, 255)};
    al_draw_text(font_, white, static_cast<float>(x), static_cast<float>(y),
                 ALLEGRO_ALIGN_CENTER, text.c_str());
}

void Screen::updateSize()
{
    width_ = static_cast<unsigned int>(
        al_get_display_width(al_get_current_display()));
    height_ = static_cast<unsigned int>(
        al_get_display_height(al_get_current_display()));
}

unsigned int Screen::getWidth() const { return width_; }

unsigned int Screen::getHeight() const { return height_; }

std::pair<unsigned int, unsigned int> Screen::getCenter() const
{
    return {width_ / 2, height_ / 2};
}

unsigned int Screen::getCenterX() const { return width_ / 2; }

unsigned int Screen::getCenterY() const { return height_ / 2; }
