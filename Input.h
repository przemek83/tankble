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
