#pragma once

#include "Input.h"

struct ALLEGRO_EVENT_QUEUE;
union ALLEGRO_EVENT;
struct ALLEGRO_KEYBOARD_STATE;
enum class InputAction : char;

class StandardInput : public Input
{
public:
    StandardInput();

    static void init();

    InputAction getMenuAction() override;

    std::set<InputAction> getGameActions() override;

    std::pair<int, int> getMousePosition() const override;

private:
    static InputAction getCommonAction(const ALLEGRO_EVENT& event);

    static bool itemPicked(const ALLEGRO_EVENT& event);

    static bool fired(const ALLEGRO_KEYBOARD_STATE& keyState);

    static bool userWantToExit(const ALLEGRO_EVENT& event);

    static bool keyEscapeUsed(const ALLEGRO_EVENT& event);

    static bool keyUpUsed(const ALLEGRO_EVENT& event);

    static bool keyDownUsed(const ALLEGRO_EVENT& event);

    static bool keyUpPressed(const ALLEGRO_KEYBOARD_STATE& keyState);

    static bool keyDownPressed(const ALLEGRO_KEYBOARD_STATE& keyState);

    static bool keyLeftPressed(const ALLEGRO_KEYBOARD_STATE& keyState);

    static bool keyRightPressed(const ALLEGRO_KEYBOARD_STATE& keyState);

    static bool keyEnterUsed(const ALLEGRO_EVENT& event);

    static bool keySpaceUsed(const ALLEGRO_EVENT& event);

    static bool mouseClickUsed(const ALLEGRO_EVENT& event);

    ALLEGRO_EVENT_QUEUE* events_;

    int mouseX_{0};

    int mouseY_{0};
};
