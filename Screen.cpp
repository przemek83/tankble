#include "Screen.h"

#include "allegro5/allegro_font.h"

#include "Config.h"

Screen::Screen(Resources resources)
    : resources_(std::move(resources)),
      width_(Config::getInstance().getBoardWidth()),
      height_(Config::getInstance().getBoardHeight()),
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

void Screen::drawBackground(ResourceType resourceType) const
{
    ALLEGRO_BITMAP* bitmapToUse{resources_.getBitmap(resourceType)};
    al_draw_scaled_bitmap(bitmapToUse, 0., 0.,
                          static_cast<float>(al_get_bitmap_width(bitmapToUse)),
                          static_cast<float>(al_get_bitmap_height(bitmapToUse)),
                          0., 0., static_cast<float>(getWidth()),
                          static_cast<float>(getHeight()), 0);
}

void Screen::drawBitmap(ResourceType resourceType, unsigned int x,
                        unsigned int y) const
{
    ALLEGRO_BITMAP* bitmapToUse{resources_.getBitmap(resourceType)};
    al_draw_bitmap(bitmapToUse, static_cast<float>(x), static_cast<float>(y),
                   0);
}

void Screen::drawScaledBitmap(ResourceType resourceType, unsigned int x,
                              unsigned int y, int size) const
{
    ALLEGRO_BITMAP* bitmapToUse{resources_.getBitmap(resourceType)};
    al_draw_scaled_bitmap(
        bitmapToUse, 0, 0, static_cast<float>(al_get_bitmap_width(bitmapToUse)),
        static_cast<float>(al_get_bitmap_height(bitmapToUse)),
        static_cast<float>(x), static_cast<float>(y), static_cast<float>(size),
        static_cast<float>(size), 0);
}

void Screen::drawScaledBitmapWithRotation(ResourceType resourceType,
                                          unsigned int x, unsigned int y,
                                          int size, unsigned int degrees) const
{
    ALLEGRO_BITMAP* bitmapToUse{resources_.getBitmap(resourceType)};
    const auto width = static_cast<float>(al_get_bitmap_width(bitmapToUse));

    al_draw_scaled_rotated_bitmap(
        bitmapToUse, width / 2.F, width / 2.F,
        static_cast<float>(x) + static_cast<float>(size) / 2.F,
        static_cast<float>(y) + static_cast<float>(size) / 2.F,
        static_cast<float>(size) / width, static_cast<float>(size) / width,
        degrees * (ALLEGRO_PI / 180), 0);
}

void Screen::clearScreenWithBlack()
{
    const ALLEGRO_COLOR blackColor{0, 0, 255, 0};
    al_set_target_bitmap(al_get_backbuffer(al_get_current_display()));
    al_clear_to_color(blackColor);
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

unsigned int Screen::getBitmapWidth(ResourceType resourceType) const
{
    return static_cast<unsigned int>(
        al_get_bitmap_width(resources_.getBitmap(resourceType)));
}

unsigned int Screen::getBitmapHeight(ResourceType resourceType) const
{
    return static_cast<unsigned int>(
        al_get_bitmap_height(resources_.getBitmap(resourceType)));
}

void Screen::refresh() { al_flip_display(); }

void Screen::showMouse() { al_show_mouse_cursor(al_get_current_display()); }

void Screen::hideMouse() { al_hide_mouse_cursor(al_get_current_display()); }

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

const Resources& Screen::getResources() const { return resources_; }
