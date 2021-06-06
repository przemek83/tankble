#pragma once

#include <utility>

struct ALLEGRO_EVENT_QUEUE;
union ALLEGRO_EVENT;

class Input final
{
public:
    Input();

    enum class Action : unsigned char
    {
        EMPTY = 0,
        TIMER,
        UP,
        DOWN,
        LEFT,
        RIGHT,
        ACCEPT,
        FIRE,
        CLICK,
        MOUSE_MOVE,
        BACK,
        QUIT
    };

    Action getAction();

    bool empty() const;

    std::pair<unsigned int, unsigned int> getMousePosition() const;

private:
    bool itemPicked(const ALLEGRO_EVENT& event) const;

    bool userWantToExit(const ALLEGRO_EVENT& event) const;

    bool keyEscapeUsed(const ALLEGRO_EVENT& event) const;

    bool keyUpUsed(const ALLEGRO_EVENT& event) const;

    bool keyDownUsed(const ALLEGRO_EVENT& event) const;

    bool keyEnterUsed(const ALLEGRO_EVENT& event) const;

    bool keySpaceUsed(const ALLEGRO_EVENT& event) const;

    bool mouseClickUsed(const ALLEGRO_EVENT& event) const;

    ALLEGRO_EVENT_QUEUE* events_;

    unsigned int mouseX_{0};

    unsigned int mouseY_{0};
};
