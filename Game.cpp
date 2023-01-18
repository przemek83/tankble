#include "Game.h"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <thread>

#include "Config.h"
#include "Input.h"
#include "InputAction.h"
#include "Map.h"
#include "Screen.h"
#include "Tank.h"

Game::Game(Screen& screen) : screen_(screen)
{
}

void Game::movement(Tank& myTank, Map& map,
                    const std::set<InputAction>& actions)
{
    const int pomX = myTank.getX() / Config::elementSize;
    const int pomY = myTank.getY() / Config::elementSize;
    const int tol = 15;

    if (actions.find(InputAction::UP) != actions.end())
    {
        myTank.move(0);
    }
    else if (actions.find(InputAction::DOWN) != actions.end())
    {
        myTank.move(2);
    }
    else if (actions.find(InputAction::LEFT) != actions.end())
    {
        myTank.move(3);
    }
    else if (actions.find(InputAction::RIGHT) != actions.end())
    {
        myTank.move(1);
    }
    if (!map.isValid(
            myTank.getX() + myTank.getDirectionX() + myTank.getDirectionX(),
            myTank.getY() + myTank.getDirectionY() + myTank.getDirectionY()))
    {
        return;
    }

    if (myTank.getDirectionX() == 0 && myTank.getDirectionY() != 0)
    {
        if (myTank.getY() % Config::elementSize == 0)
        {
            if (myTank.getX() % Config::elementSize == 0)
            {
                if (map.canDrive(pomX, pomY + myTank.getDirectionY()))
                {
                    myTank.go();
                }
            }
            else
            {
                if (map.canDrive(pomX, pomY + myTank.getDirectionY()) &&
                    map.canDrive(pomX + 1, pomY + myTank.getDirectionY()))
                {
                    myTank.go();
                }
                else
                {
                    if (map.canDrive(pomX, pomY + myTank.getDirectionY()) &&
                        myTank.getX() % Config::elementSize <= tol)
                    {
                        myTank.setX(pomX * Config::elementSize);
                        myTank.go();
                    }
                    else if (map.canDrive(pomX + 1,
                                          pomY + myTank.getDirectionY()) &&
                             myTank.getX() % Config::elementSize >=
                                 Config::elementSize - tol)
                    {
                        myTank.setX((pomX + 1) * Config::elementSize);
                        myTank.go();
                    }
                }
            }
        }
        else
        {
            myTank.go();
        }
    }
    else if (myTank.getDirectionY() == 0 && myTank.getDirectionX() != 0)
    {
        if (myTank.getX() % Config::elementSize == 0)
        {
            if (myTank.getY() % Config::elementSize == 0)
            {
                if (map.canDrive(pomX + myTank.getDirectionX(), pomY))
                {
                    myTank.go();
                }
            }
            else
            {
                if (map.canDrive(pomX + myTank.getDirectionX(), pomY) &&
                    map.canDrive(pomX + myTank.getDirectionX(), pomY + 1))
                {
                    myTank.go();
                }
                else
                {
                    if (map.canDrive(pomX + myTank.getDirectionX(), pomY) &&
                        myTank.getY() % Config::elementSize <= tol)
                    {
                        myTank.setY(pomY * Config::elementSize);
                        myTank.go();
                    }
                    else if (map.canDrive(pomX + myTank.getDirectionX(),
                                          pomY + 1) &&
                             myTank.getY() % Config::elementSize >=
                                 Config::elementSize - tol)
                    {
                        myTank.setY((pomY + 1) * Config::elementSize);
                        myTank.go();
                    }
                }
            }
        }
        else
        {
            myTank.go();
        }
    }
    map.setPower(myTank);
}

bool Game::play()
{
    Map map(screen_.getResources());

    std::cout << "Map loaded" << std::endl;

    Input input;
    bool shouldRedraw{true};
    Screen::clearScreenWithBlack();

    while (true)
    {
        const InputAction action{input.getMenuAction()};
        if (action == InputAction::BACK || isGameEnding(map))
            break;

        if (action == InputAction::QUIT)
            return false;

        if (action == InputAction::TIMER)
            shouldRedraw = true;

        if (shouldRedraw && input.isEmpty())
        {
            shouldRedraw = false;
            map.drawBackground(screen_);
            map.drawVehicles(screen_);
            map.drawBullets(screen_);
            map.drawPowers(screen_);
            map.drawForeground(screen_);
            drawStatusPlaceholder();
            control(map);
            map.moveBullet();
            Screen::refresh();
        }
    }

    std::cout << "stop" << '\n';

    return true;
}

void Game::drawStatusPlaceholder()
{
    screen_.drawText(Config::width - Config::statusPlaceholderWidth / 2,
                     Config::height / 2, "[Status placeholder]");
}

void Game::control(Map& map)
{
    for (auto& tank : map.getTanks())
    {
        if (tank.isPlayerControlled())
        {
            const auto actions{Input::getGameActions()};
            if (isPlayerMoving(actions))
                movement(tank, map, actions);

            if (actions.find(InputAction::FIRE) != actions.end())
                tank.fire(map);
        }
        else
        {
            tank.moveRandom(map);
            tank.fire(map);
        }
    }
}

void Game::drawEndOfGame(const std::string& text)
{
    Screen::clearScreenWithBlack();
    screen_.drawText(Config::width / 2, Config::height / 2, text);
    Screen::refresh();
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

bool Game::isPlayerMoving(const std::set<InputAction>& actions)
{
    return std::find_if(actions.begin(), actions.end(),
                        [](InputAction action)
                        {
                            return action == InputAction::UP ||
                                   action == InputAction::DOWN ||
                                   action == InputAction::LEFT ||
                                   action == InputAction::RIGHT;
                        }) != actions.end();
}

bool Game::isGameEnding(Map& map)
{
    if (map.isPlayerDestroyed())
    {
        drawEndOfGame("You loose");
        return true;
    }

    if (map.getTanks().size() == 1)
    {
        drawEndOfGame("You Win");
        return true;
    }

    return false;
}
