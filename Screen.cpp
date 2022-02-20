#include "Screen.h"

#include "allegro5/allegro_font.h"

#include "Config.h"

Screen::Screen(Resources resources)
    : resources_(std::move(resources)),
      width_(Config::width),
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

void Screen::drawBackground(Resources::Bitmap bitmap) const
{
    ALLEGRO_BITMAP* bitmapToUse{resources_.getBitmap(bitmap)};
    al_draw_scaled_bitmap(bitmapToUse, 0., 0.,
                          static_cast<float>(al_get_bitmap_width(bitmapToUse)),
                          static_cast<float>(al_get_bitmap_height(bitmapToUse)),
                          0., 0., static_cast<float>(getWidth()),
                          static_cast<float>(getHeight()), 0);
}

void Screen::drawBitmap(Resources::Bitmap bitmap, unsigned int x,
                        unsigned int y) const
{
    ALLEGRO_BITMAP* bitmapToUse{resources_.getBitmap(bitmap)};
    al_draw_bitmap(bitmapToUse, static_cast<float>(x), static_cast<float>(y),
                   0);
}

void Screen::clearScreenWithColor(ALLEGRO_COLOR color)
{
    al_set_target_bitmap(al_get_backbuffer(al_get_current_display()));
    al_clear_to_color(color);
    al_flip_display();
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

unsigned int Screen::getBitmapWidth(Resources::Bitmap bitmap) const
{
    return static_cast<unsigned int>(
        al_get_bitmap_width(resources_.getBitmap(bitmap)));
}

unsigned int Screen::getBitmapHeight(Resources::Bitmap bitmap) const
{
    return static_cast<unsigned int>(
        al_get_bitmap_height(resources_.getBitmap(bitmap)));
}

void Screen::refresh() const { al_flip_display(); }

void Screen::showMouse() const
{
    al_show_mouse_cursor(al_get_current_display());
}

void Screen::hideMouse() const
{
    al_hide_mouse_cursor(al_get_current_display());
}

void Screen::useFullScreenMode()
{
    al_set_display_flag(al_get_current_display(), ALLEGRO_FULLSCREEN_WINDOW,
                        true);
    updateSize();
}

void Screen::useWindowedMode()
{
    al_set_display_flag(al_get_current_display(), ALLEGRO_FULLSCREEN_WINDOW,
                        false);
    updateSize();
}
