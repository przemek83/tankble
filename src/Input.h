#pragma once

#include <set>
#include <utility>

enum class InputAction : char;

class Input
{
public:
    virtual ~Input() = default;

    virtual InputAction getMenuAction() = 0;

    virtual std::set<InputAction> getGameActions() = 0;

    virtual std::pair<int, int> getMousePosition() const = 0;
};
