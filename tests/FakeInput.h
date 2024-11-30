#pragma once

#include <vector>

#include <src/Input.h>
#include <src/InputAction.h>

class FakeInput : public Input
{
public:
    FakeInput(std::vector<InputAction> menuInputActions,
              std::set<InputAction> gameInputActions,
              std::pair<int, int> mousePosition)
        : menuInputActions_{menuInputActions},
          gameInputActions_{std::move(gameInputActions)},
          mousePosition_{mousePosition}
    {
    }

    InputAction getMenuAction() override
    {
        InputAction action{menuInputActions_.front()};
        menuInputActions_.erase(menuInputActions_.begin());
        return action;
    }

    std::set<InputAction> getGameActions() override
    {
        return gameInputActions_;
    }

    std::pair<int, int> getMousePosition() const override
    {
        return mousePosition_;
    }

private:
    std::vector<InputAction> menuInputActions_;

    std::set<InputAction> gameInputActions_;

    std::pair<int, int> mousePosition_;
};
