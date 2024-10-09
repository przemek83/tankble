#include "Screen.h"

#include <iostream>

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "Config.h"

Screen::~Screen() { ::al_destroy_font(font_); }

bool Screen::init()
{
    if (!al_init())
    {
        std::cerr << "failed to initialize allegro!\n";
        return false;
    }

    const int screenWidth{Config::getInstance().getBoardWidth() +
                          Config::getInstance().getSatusWidth()};
    const int screenHeight{Config::getInstance().getBoardHeight()};
    if (const auto* display{::al_create_display(screenWidth, screenHeight)};
        display == nullptr)
    {
        std::cerr << "failed to create display!\n";
        return false;
    }

    ::al_clear_to_color(::al_map_rgb(0, 0, 0));
    ::al_flip_display();

    ::al_init_image_addon();
    ::al_init_font_addon();
    ::al_init_primitives_addon();

    ::al_set_window_title(::al_get_current_display(), "TankBle");

    font_ = ::al_create_builtin_font();

    return true;
}

void Screen::drawText(int x, int y, const std::string& text) const
{
    const ALLEGRO_COLOR white{::al_map_rgb(255, 255, 255)};
    ::al_draw_text(font_, white, static_cast<float>(x), static_cast<float>(y),
                   ALLEGRO_ALIGN_CENTER, text.c_str());
}

void Screen::drawTextWithBackground(int x, int y, const std::string& text) const
{
    const int margin{10};
    const float radius{10};
    const int height{::al_get_font_line_height(font_)};
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
    ALLEGRO_BITMAP* bitmap{resources_.getBitmap(resourceType)};
    ::al_draw_scaled_bitmap(
        bitmap, 0., 0., getBitmapWidth(bitmap), getBitmapHeight(bitmap), 0., 0.,
        static_cast<float>(getWidth()), static_cast<float>(getHeight()), 0);
}

void Screen::drawScaledBitmap(ResourceType resourceType, int x, int y,
                              int width, int height) const
{
    ALLEGRO_BITMAP* bitmap{resources_.getBitmap(resourceType)};
    ::al_draw_scaled_bitmap(bitmap, 0, 0, getBitmapWidth(bitmap),
                            getBitmapHeight(bitmap), static_cast<float>(x),
                            static_cast<float>(y), static_cast<float>(width),
                            static_cast<float>(height), 0);
}

void Screen::drawScaledBitmapWithRotation(ResourceType resourceType, int x,
                                          int y, int size, int degrees) const
{
    ALLEGRO_BITMAP* bitmap{resources_.getBitmap(resourceType)};
    const float width{getBitmapWidth(bitmap)};
    const float halfRatio{2.F};
    const float sizeAsFloat{static_cast<float>(size)};
    ::al_draw_scaled_rotated_bitmap(
        bitmap, width / halfRatio, width / halfRatio,
        static_cast<float>(x) + (sizeAsFloat / halfRatio),
        static_cast<float>(y) + (sizeAsFloat / halfRatio), sizeAsFloat / width,
        sizeAsFloat / width,
        ((static_cast<float>(degrees) * static_cast<float>(ALLEGRO_PI)) /
         180.F),
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
    setWidth(::al_get_display_width(::al_get_current_display()));
    setHeight(::al_get_display_height(::al_get_current_display()));

    Config::getInstance().screenSizeChanged(getWidth(), getHeight());
}

int Screen::getResourceWidth(ResourceType resourceType) const
{
    return ::al_get_bitmap_width(resources_.getBitmap(resourceType));
}

int Screen::getResourceHeight(ResourceType resourceType) const
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

float Screen::getBitmapWidth(ALLEGRO_BITMAP* bitmap) const
{
    return static_cast<float>(::al_get_bitmap_width(bitmap));
}
float Screen::getBitmapHeight(ALLEGRO_BITMAP* bitmap) const
{
    return static_cast<float>(::al_get_bitmap_height(bitmap));
}
