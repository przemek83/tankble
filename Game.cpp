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

Game::Game(Screen& screen) : screen_(screen) {}

std::pair<bool, Direction> Game::inputActionsToDirection(
    const std::set<InputAction>& actions)
{
    if (actions.find(InputAction::UP) != actions.end())
        return {true, Direction::UP};

    if (actions.find(InputAction::DOWN) != actions.end())
        return {true, Direction::DOWN};

    if (actions.find(InputAction::LEFT) != actions.end())
        return {true, Direction::LEFT};

    if (actions.find(InputAction::RIGHT) != actions.end())
        return {true, Direction::RIGHT};

    return {false, Direction::UP};
}

std::vector<Point> Game::getMovingPoints(Point leftUpperCorner,
                                         Direction direction)
{
    const unsigned int oneThirdOfTank{Config::getInstance().getElementSize() /
                                      3};
    switch (direction)
    {
        case Direction::UP:
        {
            return {
                {leftUpperCorner.x + oneThirdOfTank, leftUpperCorner.y},
                {leftUpperCorner.x + 2 * oneThirdOfTank, leftUpperCorner.y}};
        }
        case Direction::DOWN:
        {
            return {{leftUpperCorner.x + oneThirdOfTank,
                     leftUpperCorner.y +
                         Config::getInstance().getElementSize() - 1},
                    {leftUpperCorner.x + 2 * oneThirdOfTank,
                     leftUpperCorner.y +
                         Config::getInstance().getElementSize() - 1}};
        }
        case Direction::LEFT:
        {
            return {
                {leftUpperCorner.x, leftUpperCorner.y + oneThirdOfTank},
                {leftUpperCorner.x, leftUpperCorner.y + 2 * oneThirdOfTank}};
        }
        case Direction::RIGHT:
        {
            return {
                {leftUpperCorner.x + Config::getInstance().getElementSize() - 1,
                 leftUpperCorner.y + oneThirdOfTank},
                {leftUpperCorner.x + Config::getInstance().getElementSize() - 1,
                 leftUpperCorner.y + 2 * oneThirdOfTank}};
        }
    }

    return {};
}

bool Game::tankIsInMap(const Map& map, int newX, int newY)
{
    const int sizeOfElementMinusOnePixel{
        static_cast<int>(Config::getInstance().getElementSize()) - 1};
    return map.isValid(newX, newY) &&
           map.isValid(newX + sizeOfElementMinusOnePixel, newY) &&
           map.isValid(newX, newY + sizeOfElementMinusOnePixel) &&
           map.isValid(newX + sizeOfElementMinusOnePixel,
                       newY + sizeOfElementMinusOnePixel);
}

void Game::shiftIfNeeded(Point& point, const Map& map, Direction direction)
{
    switch (direction)
    {
        case Direction::UP:
        case Direction::DOWN:
        {
            if (!map.canDrive(point) ||
                !map.canDrive(
                    {point.x,
                     point.y + Config::getInstance().getElementSize() - 1}))
                point.x =
                    (point.x / Config::getInstance().getElementSize() + 1) *
                    Config::getInstance().getElementSize();

            if (!map.canDrive(
                    {point.x + Config::getInstance().getElementSize() - 1,
                     point.y}) ||
                !map.canDrive(
                    {point.x + Config::getInstance().getElementSize() - 1,
                     point.y + Config::getInstance().getElementSize() - 1}))
                point.x = (point.x / Config::getInstance().getElementSize()) *
                          Config::getInstance().getElementSize();
            break;
        }

        case Direction::LEFT:
        case Direction::RIGHT:
        {
            if (!map.canDrive(point) ||
                !map.canDrive(
                    {point.x + Config::getInstance().getElementSize() - 1,
                     point.y}))
                point.y =
                    (point.y / Config::getInstance().getElementSize() + 1) *
                    Config::getInstance().getElementSize();

            if (!map.canDrive(
                    {point.x,
                     point.y + Config::getInstance().getElementSize() - 1}) ||
                !map.canDrive(
                    {point.x + Config::getInstance().getElementSize() - 1,
                     point.y + Config::getInstance().getElementSize() - 1}))
                point.y = (point.y / Config::getInstance().getElementSize()) *
                          Config::getInstance().getElementSize();
            break;
        }
    }
}

void Game::movement(Tank& tank, Map& map, Direction direction)
{
    tank.setDirection(direction);
    auto [newX, newY]{tank.getNextExpectedPosition()};
    if (!tankIsInMap(map, newX, newY))
        return;

    const auto pointsToCheck{getMovingPoints(
        {static_cast<unsigned int>(newX), static_cast<unsigned int>(newY)},
        direction)};
    if (std::all_of(pointsToCheck.cbegin(), pointsToCheck.cend(),
                    [&map](Point point) { return map.canDrive(point); }))
    {
        Point newPoint{static_cast<unsigned int>(newX),
                       static_cast<unsigned int>(newY)};
        if (tank.isPlayerControlled())
            shiftIfNeeded(newPoint, map, direction);
        tank.move(newPoint);
    }
}

bool Game::play()
{
    Map map(Config::getInstance().getMapSize());
    std::vector<Tank> tanks{map.loadMap(Resources::getLevel())};
    Input input;
    Screen::clearScreenWithBlack();
    std::list<Bullet> bullets;

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
    screen_.drawText(Config::getInstance().getBoardWidth() +
                         Config::getInstance().getSatusWidth() / 2,
                     Config::getInstance().getBoardHeight() / 2,
                     "[Status placeholder]");
}

void Game::control(Map& map, std::vector<Tank>& tanks,
                   std::list<Bullet>& bullets)
{
    moveBullets(bullets, tanks, map);

    for (auto& tank : tanks)
    {
        Direction direction{Direction::UP};
        if (tank.isPlayerControlled())
        {
            setPower(tank, map);
            const auto actions{Input::getGameActions()};
            if (actions.find(InputAction::FIRE) != actions.end() &&
                tank.canFire())
                bullets.emplace_back(tank.fire());

            bool shouldMove{false};
            std::tie(shouldMove, direction) = inputActionsToDirection(actions);
            if (!shouldMove)
                continue;
        }
        else
        {
            if (tank.canFire())
                bullets.emplace_back(tank.fire());
            const int i{rand() % 8};
            if (tank.getX() % Config::getInstance().getElementSize() == 0 &&
                tank.getY() % Config::getInstance().getElementSize() == 0 &&
                i < 4)
                direction = static_cast<Direction>(i);
            else
                direction = tank.getDirection();
        }
        movement(tank, map, direction);
    }
}

void Game::drawEndOfGame(const std::string& text)
{
    Screen::clearScreenWithBlack();
    screen_.drawText((Config::getInstance().getBoardWidth() +
                      Config::getInstance().getSatusWidth()) /
                         2,
                     Config::getInstance().getBoardHeight() / 2, text);
    Screen::refresh();
    std::this_thread::sleep_for(std::chrono::seconds(2));
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

void Game::moveBullets(std::list<Bullet>& bullets, std::vector<Tank>& tanks,
                       Map& map)
{
    for (auto bulletIter = bullets.begin(); bulletIter != bullets.end();)
    {
        bool valid{bulletIter->move()};
        if (const Point bulletCenter{bulletIter->getCenter()};
            valid && !map.canFly(bulletCenter))
        {
            map.destroyItem(bulletCenter, bulletIter->getPower());
            valid = false;
        }

        if (auto tankIter{hitTank(*bulletIter, tanks)};
            valid && tankIter != tanks.end())
        {
            if (tankIter->hit(bulletIter->getPower()))
            {
                if (tankIter->isPlayerControlled())
                    playerDestroyed_ = true;
                tanks.erase(tankIter);
            }
            valid = false;
        }
        bulletIter = (valid ? ++bulletIter : bullets.erase(bulletIter));
    }
}

std::vector<Tank>::iterator Game::hitTank(const Bullet& bullet,
                                          std::vector<Tank>& tanks)
{
    return std::find_if(tanks.begin(), tanks.end(),
                        [&bullet](const auto& tank)
                        {
                            return tank.isWithin(bullet.getCenter()) &&
                                   bullet.getTankType() != tank.getTankType();
                        });
}

void Game::drawBullets(const std::list<Bullet>& bullets)
{
    for (const auto& bullet : bullets)
        bullet.draw(screen_);
}

void Game::draw(const std::list<Bullet>& bullets,
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
