#include "StandardInput.h"

#include <allegro5/allegro.h>

#include "Config.h"
#include "InputAction.h"

StandardInput::StandardInput() : events_(::al_create_event_queue())
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

void StandardInput::init()
{
    ::al_install_keyboard();
    ::al_install_mouse();
}

InputAction StandardInput::getMenuAction()
{
    ALLEGRO_EVENT event;
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

std::set<InputAction> StandardInput::getGameActions()
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

std::pair<int, int> StandardInput::getMousePosition() const
{
    return {mouseX_, mouseY_};
}

InputAction StandardInput::getCommonAction(const ALLEGRO_EVENT& event)
{
    if (userWantToExit(event))
        return InputAction::QUIT;

    if (keyEscapeUsed(event))
        return InputAction::BACK;

    if (event.type == ALLEGRO_EVENT_TIMER)
        return InputAction::TIMER;

    return InputAction::EMPTY;
}

bool StandardInput::itemPicked(const ALLEGRO_EVENT& event)
{
    return keyEnterUsed(event) || keySpaceUsed(event) || mouseClickUsed(event);
}

bool StandardInput::fired(const ALLEGRO_KEYBOARD_STATE& keyState)
{
    return ::al_key_down(&keyState, ALLEGRO_KEY_SPACE) ||
           ::al_key_down(&keyState, ALLEGRO_KEY_ENTER);
}

bool StandardInput::userWantToExit(const ALLEGRO_EVENT& event)
{
    return event.type == ALLEGRO_EVENT_DISPLAY_CLOSE;
}

bool StandardInput::keyEscapeUsed(const ALLEGRO_EVENT& event)
{
    return (event.type == ALLEGRO_EVENT_KEY_CHAR) &&
           (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE);
}

bool StandardInput::keyUpUsed(const ALLEGRO_EVENT& event)
{
    return (event.type == ALLEGRO_EVENT_KEY_CHAR) &&
           (event.keyboard.keycode == ALLEGRO_KEY_UP);
}

bool StandardInput::keyDownUsed(const ALLEGRO_EVENT& event)
{
    return (event.type == ALLEGRO_EVENT_KEY_CHAR) &&
           (event.keyboard.keycode == ALLEGRO_KEY_DOWN);
}

bool StandardInput::keyUpPressed(const ALLEGRO_KEYBOARD_STATE& keyState)
{
    return ::al_key_down(&keyState, ALLEGRO_KEY_UP);
}

bool StandardInput::keyDownPressed(const ALLEGRO_KEYBOARD_STATE& keyState)
{
    return ::al_key_down(&keyState, ALLEGRO_KEY_DOWN);
}

bool StandardInput::keyLeftPressed(const ALLEGRO_KEYBOARD_STATE& keyState)
{
    return ::al_key_down(&keyState, ALLEGRO_KEY_LEFT);
}

bool StandardInput::keyRightPressed(const ALLEGRO_KEYBOARD_STATE& keyState)
{
    return ::al_key_down(&keyState, ALLEGRO_KEY_RIGHT);
}

bool StandardInput::keyEnterUsed(const ALLEGRO_EVENT& event)
{
    return (event.type == ALLEGRO_EVENT_KEY_UP) &&
           (event.keyboard.keycode == ALLEGRO_KEY_ENTER);
}

bool StandardInput::keySpaceUsed(const ALLEGRO_EVENT& event)
{
    return (event.type == ALLEGRO_EVENT_KEY_UP) &&
           (event.keyboard.keycode == ALLEGRO_KEY_SPACE);
}

bool StandardInput::mouseClickUsed(const ALLEGRO_EVENT& event)
{
    return (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) &&
           (event.mouse.button == 1);
}
