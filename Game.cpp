#include "Game.h"

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>

#include "Bullet.h"
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
    setPower(myTank, map);
}

bool Game::play()
{
    Map map;
    std::vector<Tank> tanks{map.loadMap(screen_.getResources().getLevel())};
    Input input;
    Screen::clearScreenWithBlack();
    std::vector<Bullet> bullets;

    while (true)
    {
        const InputAction action{input.getMenuAction()};
        if (action == InputAction::BACK || isGameEnding(map, tanks))
            break;

        if (action == InputAction::QUIT)
            return false;

        if (action == InputAction::TIMER)
        {
            draw(bullets, tanks, map);
            control(map, tanks, bullets);
            Screen::refresh();
        }
    }

    return true;
}

void Game::drawStatusPlaceholder()
{
    screen_.drawText(Config::width - Config::statusPlaceholderWidth / 2,
                     Config::height / 2, "[Status placeholder]");
}

void Game::control(Map& map, std::vector<Tank>& tanks,
                   std::vector<Bullet>& bullets)
{
    moveBullets(bullets, tanks, map);

    for (auto& tank : tanks)
    {
        if (tank.isPlayerControlled())
        {
            const auto actions{Input::getGameActions()};
            if (isPlayerMoving(actions))
                movement(tank, map, actions);

            if (actions.find(InputAction::FIRE) != actions.end() &&
                tank.canFire())
                bullets.emplace_back(tank);
        }
        else
        {
            tank.moveRandom(map);
            if (tank.canFire())
                bullets.emplace_back(tank);
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

bool Game::isGameEnding(const Map& map, const std::vector<Tank>& tanks)
{
    if (map.isPlayerDestroyed() || playerDestroyed_)
    {
        drawEndOfGame("You loose");
        return true;
    }

    if (tanks.size() == 1)
    {
        drawEndOfGame("You Win");
        return true;
    }

    return false;
}

void Game::drawTanks(const std::vector<Tank>& tanks)
{
    for (const auto& tank : tanks)
        tank.draw(screen_);
}

void Game::moveBullets(std::vector<Bullet>& bullets, std::vector<Tank>& tanks,
                       Map& map)
{
    for (int i = static_cast<int>(bullets.size()) - 1; i >= 0; i--)
    {
        Bullet& bullet{bullets.at(i)};
        if (bullet.move())
        {
            const Point bulletCenter{bullet.getCenter()};
            const int iter{isTank(bullet, tanks)};
            if (!map.canFly(bulletCenter))
            {
                map.destroyItem(bulletCenter, bullet.getPower());
                bullets.erase(bullets.begin() + i);
            }
            if (iter >= 0)
            {
                Tank& tank{tanks.at(iter)};
                if (tank.destroy(bullet.getPower()))
                {
                    if (tank.isPlayerControlled())
                        playerDestroyed_ = true;
                    tanks.erase(tanks.begin() + iter);
                }
                bullets.erase(bullets.begin() + i);
            }
        }
        else
        {
            bullets.erase(bullets.begin() + i);
        }
    }
}

int Game::isTank(const Bullet& bullet, std::vector<Tank>& tanks)
{
    for (unsigned int i = 0; i < tanks.size(); i++)
    {
        const Point bulletCenter{bullet.getCenter()};
        const Tank& v{tanks.at(i)};
        if (bulletCenter.x >= v.getX() &&
            bulletCenter.x < v.getX() + Config::elementSize &&
            bulletCenter.y >= v.getY() &&
            bulletCenter.y < v.getY() + Config::elementSize &&
            bullet.getTankType() != v.getTankType())
        {  // check friendly fire
            return i;
        }
    }
    return -1;
}

void Game::drawBullets(const std::vector<Bullet>& bullets)
{
    for (const auto& bullet : bullets)
        bullet.draw(screen_);
}

void Game::draw(const std::vector<Bullet>& bullets,
                const std::vector<Tank>& tanks, Map& map)
{
    map.drawBackground(screen_);
    drawTanks(tanks);
    drawBullets(bullets);
    map.drawForeground(screen_);
    drawStatusPlaceholder();
}

void Game::setPower(Tank& tank, Map& map)
{
    if (auto [takenPowerUp, powerUp]{map.takePowerUp(tank.getCenter())};
        takenPowerUp)
        tank.applyPowerUp(powerUp);
}
