#pragma once

#include <utility>

struct ALLEGRO_EVENT_QUEUE;
union ALLEGRO_EVENT;
enum class InputAction : unsigned char;

class Input final
{
public:
    Input();

    InputAction getAction();

    bool isEmpty() const;

    std::pair<unsigned int, unsigned int> getMousePosition() const;

private:
    static bool itemPicked(const ALLEGRO_EVENT& event);

    static bool userWantToExit(const ALLEGRO_EVENT& event) ;

    static bool keyEscapeUsed(const ALLEGRO_EVENT& event);

    static bool keyUpUsed(const ALLEGRO_EVENT& event);

    static bool keyDownUsed(const ALLEGRO_EVENT& event);

    static bool keyLeftUsed(const ALLEGRO_EVENT& event);

    static bool keyRightUsed(const ALLEGRO_EVENT& event);

    static bool keyEnterUsed(const ALLEGRO_EVENT& event);

    static bool keySpaceUsed(const ALLEGRO_EVENT& event);

    static bool mouseClickUsed(const ALLEGRO_EVENT& event);

    ALLEGRO_EVENT_QUEUE* events_;

    unsigned int mouseX_{0};

    unsigned int mouseY_{0};
};
