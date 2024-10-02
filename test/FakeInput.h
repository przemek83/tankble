#pragma once

#include <src/Input.h>
#include "src/InputAction.h"

class FakeInput : public Input
{
public:
    FakeInput(InputAction imenuInputAction,
              std::set<InputAction> gameInputActions,
              std::pair<int, int> mousePosition)
        : menuInputAction_{imenuInputAction},
          gameInputActions_{std::move(gameInputActions)},
          mousePosition_{mousePosition}
    {
    }

    InputAction getMenuAction() override { return menuInputAction_; }

    std::set<InputAction> getGameActions() override
    {
        return gameInputActions_;
    }

    std::pair<int, int> getMousePosition() const override
    {
        return mousePosition_;
    }

private:
    InputAction menuInputAction_;

    std::set<InputAction> gameInputActions_;

    std::pair<int, int> mousePosition_;
};
