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

void Game::drawTanks(const Screen& screen, const std::vector<Tank>& tanks)
{
    for (const auto& vehicle : tanks)
    {
        auto resourceType = static_cast<ResourceType>(
            static_cast<unsigned char>(ResourceType::PLAYER_TANK_TIER_1) +
            static_cast<unsigned char>(vehicle.getTankType()));

        screen.drawScaledBitmapWithRotation(resourceType, vehicle.getX(),
                                            vehicle.getY(), Config::elementSize,
                                            90 * vehicle.getDirection());
    }
}

void Game::moveBullets(std::vector<Bullet>& bullets, std::vector<Tank>& tanks,
                       Map& map)
{
    for (unsigned int i = 0; i < bullets.size(); i++)
    {
        Bullet& b{bullets.at(i)};
        int px{b.getX() + b.getDirectionX() * b.getSpeed()};
        int py{b.getY() + b.getDirectionY() * b.getSpeed()};
        if (isBulletValid(px, py))
        {
            b.setX(px);
            b.setY(py);
            unsigned int pi{b.getCenterY() / Config::elementSize};
            unsigned int pj{b.getCenterX() / Config::elementSize};
            int iter{isTank(b, tanks)};
            if (!map.canFly(pj, pi))
            {
                map.destroyItem(pj, pi, b.getPower());
                bullets.erase(bullets.begin() + i);
            }
            if (iter >= 0)
            {
                Tank& v{tanks.at(iter)};
                if (v.destroy(b.getPower()))
                {
                    if (v.isPlayerControlled())
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

bool Game::isBulletValid(int x, int y)
{
    const int bulletSize{7};
    return !(x >= Config::elementSize * Config::mapSize - bulletSize ||
             y >= Config::elementSize * Config::mapSize - bulletSize || y < 0 ||
             x < 0);
}

int Game::isTank(const Bullet& bullet, std::vector<Tank>& tanks)
{
    for (unsigned int i = 0; i < tanks.size(); i++)
    {
        const Tank& v{tanks.at(i)};
        if (bullet.getCenterX() >= v.getX() &&
            bullet.getCenterX() < v.getX() + Config::elementSize &&
            bullet.getCenterY() >= v.getY() &&
            bullet.getCenterY() < v.getY() + Config::elementSize &&
            bullet.getTankType() != v.getTankType())
        {  // check friendly fire
            return i;
        }
    }
    return -1;
}

void Game::drawBullets(const Screen& screen, const std::vector<Bullet>& bullets)
{
    const ResourceType resourceType = Bullet::getResourceType();
    for (const auto& bullet : bullets)
    {
        screen.drawScaledBitmap(resourceType, bullet.getX(), bullet.getY(),
                                Config::BULLET_SIZE);
    }
}

void Game::draw(const std::vector<Bullet>& bullets,
                const std::vector<Tank>& tanks, Map& map)
{
    map.drawBackground(screen_);
    drawTanks(screen_, tanks);
    drawBullets(screen_, bullets);
    map.drawForeground(screen_);
    drawStatusPlaceholder();
}

void Game::setPower(Tank& tank, Map& map)
{
    const std::size_t x{(tank.getX() + 15) / Config::elementSize};
    const std::size_t y{(tank.getY() + 15) / Config::elementSize};

    auto [takenPowerUp, powerUp]{map.takePowerUp(x, y)};
    if (!takenPowerUp)
        return;

    switch (powerUp)
    {
        case ResourceType::SHIELD_UP:
            tank.setMaxArmor();
            break;

        case ResourceType::TIER_UP:
            if (static_cast<int>(tank.getTankType()) < 3)
                tank.setType(static_cast<TankType>(
                    static_cast<int>(tank.getTankType()) + 1));
            break;

        case ResourceType::SPEED_UP:
            tank.setSpeedUp();
            break;

        case ResourceType::LIFE_UP:
            tank.addLife();
            break;

        default:
            break;
    }
}
