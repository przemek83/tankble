#include "Game.h"

#include <iostream>

#include <allegro5/allegro_font.h>

#include "Config.h"
#include "Input.h"
#include "InputAction.h"
#include "Map.h"
#include "Screen.h"
#include "Tank.h"

Game::Game(Screen& screen) : screen_(screen)
{
}

void Game::movement(Tank& myTank, Map& map)
{
    const int pomX = myTank.getX() / Config::elementSize;
    const int pomY = myTank.getY() / Config::elementSize;
    const int tol = 15;

    ALLEGRO_KEYBOARD_STATE key_state;
    al_get_keyboard_state(&key_state);

    if (al_key_down(&key_state, ALLEGRO_KEY_UP))
    {
        myTank.move(0);
    }
    else if (al_key_down(&key_state, ALLEGRO_KEY_DOWN))
    {
        myTank.move(2);
    }
    else if (al_key_down(&key_state, ALLEGRO_KEY_LEFT))
    {
        myTank.move(3);
    }
    else if (al_key_down(&key_state, ALLEGRO_KEY_RIGHT))
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

bool Game::userWantToExit(const ALLEGRO_EVENT& event)
{
    return event.type == ALLEGRO_EVENT_KEY_UP &&
           event.keyboard.keycode == ALLEGRO_KEY_ESCAPE;
}

bool Game::userWantToQuit(const ALLEGRO_EVENT& event)
{
    return event.type == ALLEGRO_EVENT_DISPLAY_CLOSE;
}

bool Game::play()
{
    Map map(screen_.getResources());

    std::cout << "Map loaded" << std::endl;

    Input input;
    bool shouldRedraw{true};
    Screen::clearScreenWithColor({0, 0, 255, 0});

    while (true)
    {
        const InputAction action{input.getAction()};

        if (action == InputAction::BACK || gameOver_)
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
    if (map.isPlayerDestroyed())
    {
        drawEndOfGame("You loose");
        gameOver_ = true;
        return;
    }

    if (map.getTanks().size() == 1)
    {
        drawEndOfGame("You Win");
        gameOver_ = true;
        return;
    }

    for (auto& tank : map.getTanks())
    {
        if (tank.isPlayerControlled())
        {
            ALLEGRO_KEYBOARD_STATE key_state;
            al_get_keyboard_state(&key_state);

            if (al_key_down(&key_state, ALLEGRO_KEY_UP) ||
                al_key_down(&key_state, ALLEGRO_KEY_DOWN) ||
                al_key_down(&key_state, ALLEGRO_KEY_LEFT) ||
                al_key_down(&key_state, ALLEGRO_KEY_RIGHT))
            {
                movement(tank, map);
            }
            if (al_key_down(&key_state, ALLEGRO_KEY_SPACE) ||
                al_key_down(&key_state, ALLEGRO_KEY_ENTER))
            {
                tank.fire(map);
            }
        }
        else
        {
            tank.moveRandom(map);
            tank.fire(map);
        }
    }

    map.moveBullet();
}

void Game::drawEndOfGame(const std::string& text)
{
    Screen::clearScreenWithColor({0, 0, 255, 0});
    screen_.drawText(Config::width / 2, Config::height / 2, text);
    Screen::refresh();
    al_rest(2);
}
