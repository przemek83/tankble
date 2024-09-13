#include "Input.h"

#include <allegro5/allegro.h>

#include "Config.h"
#include "InputAction.h"

Input::Input() : events_(::al_create_event_queue())
{
    ALLEGRO_TIMER* timer{
        ::al_create_timer(1.0 / Config::getInstance().getFps())};
    ::al_register_event_source(events_, ::al_get_keyboard_event_source());
    ::al_register_event_source(events_, ::al_get_mouse_event_source());
    ::al_register_event_source(
        events_, ::al_get_display_event_source(::al_get_current_display()));
    ::al_register_event_source(events_, ::al_get_timer_event_source(timer));
    ::al_start_timer(timer);
}

void Input::init()
{
    ::al_install_keyboard();
    ::al_install_mouse();
}

InputAction Input::getMenuAction()
{
    ALLEGRO_EVENT event{};
    ::al_wait_for_event(events_, &event);

    if (const InputAction action{getCommonAction(event)};
        action != InputAction::EMPTY)
        return action;

    if (itemPicked(event))
        return InputAction::ACCEPT;

    if (keyUpUsed(event))
        return InputAction::UP;

    if (keyDownUsed(event))
        return InputAction::DOWN;

    if (event.type != ALLEGRO_EVENT_MOUSE_AXES)
        return InputAction::EMPTY;

    if (event.mouse.x > 0)

        mouseX_ = event.mouse.x;
    else
        mouseX_ = 0;

    if (event.mouse.y > 0)

        mouseY_ = event.mouse.y;
    else
        mouseX_ = 0;

    return InputAction::MOUSE_MOVE;
}

std::set<InputAction> Input::getGameActions()
{
    ALLEGRO_KEYBOARD_STATE keyState;
    ::al_get_keyboard_state(&keyState);

    std::set<InputAction> ongoingActions{};
    if (fired(keyState))
        ongoingActions.insert(InputAction::FIRE);

    if (keyUpPressed(keyState))
        ongoingActions.insert(InputAction::UP);

    if (keyDownPressed(keyState))
        ongoingActions.insert(InputAction::DOWN);

    if (keyLeftPressed(keyState))
        ongoingActions.insert(InputAction::LEFT);

    if (keyRightPressed(keyState))
        ongoingActions.insert(InputAction::RIGHT);

    return ongoingActions;
}

std::pair<int, int> Input::getMousePosition() const
{
    return {mouseX_, mouseY_};
}

InputAction Input::getCommonAction(const ALLEGRO_EVENT& event)
{
    if (userWantToExit(event))
        return InputAction::QUIT;

    if (keyEscapeUsed(event))
        return InputAction::BACK;

    if (event.type == ALLEGRO_EVENT_TIMER)
        return InputAction::TIMER;

    return InputAction::EMPTY;
}

bool Input::itemPicked(const ALLEGRO_EVENT& event)
{
    return keyEnterUsed(event) || keySpaceUsed(event) || mouseClickUsed(event);
}

bool Input::fired(const ALLEGRO_KEYBOARD_STATE& keyState)
{
    return ::al_key_down(&keyState, ALLEGRO_KEY_SPACE) ||
           ::al_key_down(&keyState, ALLEGRO_KEY_ENTER);
}

bool Input::userWantToExit(const ALLEGRO_EVENT& event)
{
    return event.type == ALLEGRO_EVENT_DISPLAY_CLOSE;
}

bool Input::keyEscapeUsed(const ALLEGRO_EVENT& event)
{
    return (event.type == ALLEGRO_EVENT_KEY_CHAR) &&
           (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE);
}

bool Input::keyUpUsed(const ALLEGRO_EVENT& event)
{
    return (event.type == ALLEGRO_EVENT_KEY_CHAR) &&
           (event.keyboard.keycode == ALLEGRO_KEY_UP);
}

bool Input::keyDownUsed(const ALLEGRO_EVENT& event)
{
    return (event.type == ALLEGRO_EVENT_KEY_CHAR) &&
           (event.keyboard.keycode == ALLEGRO_KEY_DOWN);
}

bool Input::keyUpPressed(const ALLEGRO_KEYBOARD_STATE& keyState)
{
    return ::al_key_down(&keyState, ALLEGRO_KEY_UP);
}

bool Input::keyDownPressed(const ALLEGRO_KEYBOARD_STATE& keyState)
{
    return ::al_key_down(&keyState, ALLEGRO_KEY_DOWN);
}

bool Input::keyLeftPressed(const ALLEGRO_KEYBOARD_STATE& keyState)
{
    return ::al_key_down(&keyState, ALLEGRO_KEY_LEFT);
}

bool Input::keyRightPressed(const ALLEGRO_KEYBOARD_STATE& keyState)
{
    return ::al_key_down(&keyState, ALLEGRO_KEY_RIGHT);
}

bool Input::keyEnterUsed(const ALLEGRO_EVENT& event)
{
    return (event.type == ALLEGRO_EVENT_KEY_UP) &&
           (event.keyboard.keycode == ALLEGRO_KEY_ENTER);
}

bool Input::keySpaceUsed(const ALLEGRO_EVENT& event)
{
    return (event.type == ALLEGRO_EVENT_KEY_UP) &&
           (event.keyboard.keycode == ALLEGRO_KEY_SPACE);
}

bool Input::mouseClickUsed(const ALLEGRO_EVENT& event)
{
    return (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) &&
           (event.mouse.button == 1);
}
