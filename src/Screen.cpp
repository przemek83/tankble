#include "Screen.h"

#include <iostream>

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "Config.h"

Screen::Screen(Resources resources)
    : resources_(std::move(resources)),
      width_(Config::getInstance().getBoardWidth() +
             Config::getInstance().getSatusWidth()),
      height_(Config::getInstance().getBoardHeight()),
      font_{::al_create_builtin_font()}
{
}

Screen::~Screen() { ::al_destroy_font(font_); }

void Screen::init()
{
    if (!al_init())
    {
        std::cerr << "failed to initialize allegro!\n";
        ::abort();
    }

    const int screenWidth{
        static_cast<int>(Config::getInstance().getBoardWidth() +
                         Config::getInstance().getSatusWidth())};
    const int screenHeight{
        static_cast<int>(Config::getInstance().getBoardHeight())};
    if (::al_create_display(screenWidth, screenHeight) == nullptr)
    {
        std::cerr << "failed to create display!\n";
        ::abort();
    }

    ::al_clear_to_color(::al_map_rgb(0, 0, 0));
    ::al_flip_display();

    ::al_init_image_addon();
    ::al_init_font_addon();
    ::al_init_primitives_addon();

    ::al_set_window_title(::al_get_current_display(), "TankBle");
}

void Screen::drawText(unsigned int x, unsigned y, const std::string& text) const
{
    const ALLEGRO_COLOR white{::al_map_rgb(255, 255, 255)};
    ::al_draw_text(font_, white, static_cast<float>(x), static_cast<float>(y),
                   ALLEGRO_ALIGN_CENTER, text.c_str());
}

void Screen::drawTextWithBackground(unsigned int x, unsigned int y,
                                    const std::string& text) const
{
    const unsigned int margin{10};
    const float radius{10};
    const unsigned int height{
        static_cast<unsigned int>(::al_get_font_line_height(font_))};
    const float width{
        static_cast<float>(::al_get_text_width(font_, text.c_str()))};
    const float halfOfWidth{width / 2.F};
    ::al_draw_filled_rounded_rectangle(
        static_cast<float>(x) - halfOfWidth - margin,
        static_cast<float>(y - margin),
        static_cast<float>(x) + halfOfWidth + margin,
        static_cast<float>(y + height + margin), radius, radius,
        ::al_map_rgb(0, 0, 255));
    drawText(x, y, text);
}

void Screen::drawBackground(ResourceType resourceType) const
{
    ALLEGRO_BITMAP* bitmapToUse{resources_.getBitmap(resourceType)};
    ::al_draw_scaled_bitmap(
        bitmapToUse, 0., 0.,
        static_cast<float>(::al_get_bitmap_width(bitmapToUse)),
        static_cast<float>(::al_get_bitmap_height(bitmapToUse)), 0., 0.,
        static_cast<float>(getWidth()), static_cast<float>(getHeight()), 0);
}

void Screen::drawScaledSquareBitmap(ResourceType resourceType, unsigned int x,
                                    unsigned int y, unsigned int size) const
{
    drawScaledBitmap(resourceType, x, y, size, size);
}

void Screen::drawScaledBitmap(ResourceType resourceType, unsigned int x,
                              unsigned int y, unsigned int width,
                              unsigned int height) const
{
    ALLEGRO_BITMAP* bitmapToUse{resources_.getBitmap(resourceType)};
    ::al_draw_scaled_bitmap(
        bitmapToUse, 0, 0,
        static_cast<float>(::al_get_bitmap_width(bitmapToUse)),
        static_cast<float>(::al_get_bitmap_height(bitmapToUse)),
        static_cast<float>(x), static_cast<float>(y), static_cast<float>(width),
        static_cast<float>(height), 0);
}

void Screen::drawScaledBitmapWithRotation(ResourceType resourceType,
                                          unsigned int x, unsigned int y,
                                          unsigned int size,
                                          unsigned int degrees) const
{
    ALLEGRO_BITMAP* bitmapToUse{resources_.getBitmap(resourceType)};
    const auto width = static_cast<float>(::al_get_bitmap_width(bitmapToUse));
    const float halfRatio{2.F};
    ::al_draw_scaled_rotated_bitmap(
        bitmapToUse, width / halfRatio, width / halfRatio,
        static_cast<float>(x) + static_cast<float>(size) / halfRatio,
        static_cast<float>(y) + static_cast<float>(size) / halfRatio,
        static_cast<float>(size) / width, static_cast<float>(size) / width,
        static_cast<float>(degrees) * (static_cast<float>(ALLEGRO_PI) / 180.F),
        0);
}

void Screen::clearScreenWithBlack()
{
    const ALLEGRO_COLOR blackColor{::al_map_rgb(0, 0, 0)};
    ::al_set_target_bitmap(::al_get_backbuffer(::al_get_current_display()));
    ::al_clear_to_color(blackColor);
    ::al_flip_display();
}

void Screen::updateSize()
{
    width_ = ::al_get_display_width(::al_get_current_display());
    height_ = ::al_get_display_height(::al_get_current_display());

    Config::getInstance().screenSizeChanged(getWidth(), getHeight());
}

int Screen::getWidth() const { return width_; }

int Screen::getHeight() const { return height_; }

unsigned int Screen::getCenterX() const { return width_ / 2; }

unsigned int Screen::getCenterY() const { return height_ / 2; }

int Screen::getBitmapWidth(ResourceType resourceType) const
{
    return ::al_get_bitmap_width(resources_.getBitmap(resourceType));
}

int Screen::getBitmapHeight(ResourceType resourceType) const
{
    return ::al_get_bitmap_height(resources_.getBitmap(resourceType));
}

void Screen::refresh() { ::al_flip_display(); }

void Screen::showMouse() { ::al_show_mouse_cursor(::al_get_current_display()); }

void Screen::hideMouse() { ::al_hide_mouse_cursor(::al_get_current_display()); }

void Screen::useFullScreenMode()
{
    ::al_set_display_flag(::al_get_current_display(), ALLEGRO_FULLSCREEN_WINDOW,
                          true);
    updateSize();
}

void Screen::useWindowedMode()
{
    ::al_set_display_flag(::al_get_current_display(), ALLEGRO_FULLSCREEN_WINDOW,
                          false);
    updateSize();
}
