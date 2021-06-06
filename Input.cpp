#include "Input.h"

#include <allegro5/allegro.h>

#include "Config.h"

Input::Input() : events_(al_create_event_queue())
{
    ALLEGRO_TIMER* timer{al_create_timer(1.0 / Config::fps)};
    al_register_event_source(events_, al_get_keyboard_event_source());
    al_register_event_source(events_, al_get_mouse_event_source());
    al_register_event_source(
        events_, al_get_display_event_source(al_get_current_display()));
    al_register_event_source(events_, al_get_timer_event_source(timer));
    al_start_timer(timer);
}

Input::Action Input::getAction()
{
    ALLEGRO_EVENT event;
    al_wait_for_event(events_, &event);

    if (userWantToExit(event))
        return Action::QUIT;

    if (keyEscapeUsed(event))
        return Action::BACK;

    if (itemPicked(event))
        return Action::ACCEPT;

    if (keyUpUsed(event))
        return Action::UP;

    if (keyDownUsed(event))
        return Action::DOWN;

    if (event.type == ALLEGRO_EVENT_MOUSE_AXES)
    {
        mouseX_ =
            (event.mouse.x > 0 ? static_cast<unsigned int>(event.mouse.x) : 0);
        mouseY_ =
            (event.mouse.y > 0 ? static_cast<unsigned int>(event.mouse.y) : 0);
        return Action::MOUSE_MOVE;
    }

    if (event.type == ALLEGRO_EVENT_TIMER)
        return Action::TIMER;

    return Action::EMPTY;
}

bool Input::empty() const { return al_is_event_queue_empty(events_); }

std::pair<unsigned int, unsigned int> Input::getMousePosition() const
{
    return {mouseX_, mouseY_};
}

bool Input::itemPicked(const ALLEGRO_EVENT& event) const
{
    return keyEnterUsed(event) || keySpaceUsed(event) || mouseClickUsed(event);
}

bool Input::userWantToExit(const ALLEGRO_EVENT& event) const
{
    return event.type == ALLEGRO_EVENT_DISPLAY_CLOSE;
}

bool Input::keyEscapeUsed(const ALLEGRO_EVENT& event) const
{
    return event.type == ALLEGRO_EVENT_KEY_UP &&
           event.keyboard.keycode == ALLEGRO_KEY_ESCAPE;
}

bool Input::keyUpUsed(const ALLEGRO_EVENT& event) const
{
    return event.type == ALLEGRO_EVENT_KEY_UP &&
           event.keyboard.keycode == ALLEGRO_KEY_UP;
}

bool Input::keyDownUsed(const ALLEGRO_EVENT& event) const
{
    return event.type == ALLEGRO_EVENT_KEY_UP &&
           event.keyboard.keycode == ALLEGRO_KEY_DOWN;
}

bool Input::keyEnterUsed(const ALLEGRO_EVENT& event) const
{
    return event.type == ALLEGRO_EVENT_KEY_UP &&
           event.keyboard.keycode == ALLEGRO_KEY_ENTER;
}

bool Input::keySpaceUsed(const ALLEGRO_EVENT& event) const
{
    return event.type == ALLEGRO_EVENT_KEY_UP &&
           event.keyboard.keycode == ALLEGRO_KEY_SPACE;
}

bool Input::mouseClickUsed(const ALLEGRO_EVENT& event) const
{
    return event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP &&
           event.mouse.button == 1;
}
