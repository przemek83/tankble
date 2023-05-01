#include "Game.h"

#include <algorithm>
#include <chrono>
#include <fstream>
#include <thread>

#include "Bullet.h"
#include "Config.h"
#include "Input.h"
#include "InputAction.h"
#include "Map.h"
#include "MapUtils.h"
#include "PointUtils.h"
#include "Screen.h"
#include "Tank.h"

Game::Game(Screen& screen)
    : status_({Config::getInstance().getBoardWidth(), 0}),
      randomGenerator_(Config::getRandomSeed()),
      screen_(screen)
{
}

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

const Tank& Game::getPlayerTank(const std::list<Tank>& tanks)
{
    const auto& playerTankIter = std::find_if(
        tanks.begin(), tanks.end(),
        [](const auto& tank) { return tank.isPlayerControlled(); });
    return *playerTankIter;
}

void Game::movement(Tank& tank, Map& map, Direction direction)
{
    tank.setDirection(direction);
    auto [newX, newY]{tank.getNextExpectedPosition()};
    if (!PointUtils::isValidPoint(newX, newY,
                                  Config::getInstance().getTileSize()))
        return;

    const auto pointsToCheck{MapUtils::getMovePoints(
        {static_cast<unsigned int>(newX), static_cast<unsigned int>(newY)},
        direction)};
    if (std::all_of(pointsToCheck.cbegin(), pointsToCheck.cend(),
                    [&map](Point point) { return map.canDrive(point); }))
    {
        Point newPoint{static_cast<unsigned int>(newX),
                       static_cast<unsigned int>(newY)};
        if (tank.isPlayerControlled())
            MapUtils::shiftIfNeeded(newPoint, map, direction);
        tank.move(newPoint);
    }
}

bool Game::play()
{
    Map map(Config::getInstance().getTileCount());
    std::fstream level{Resources::getLevel()};
    std::list<Tank> tanks{map.loadMap(level)};
    level.close();

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

void Game::control(Map& map, std::list<Tank>& tanks, std::list<Bullet>& bullets)
{
    moveBullets(bullets, tanks, map);

    std::uniform_int_distribution<> distribution(0, 7);

    for (auto& tank : tanks)
    {
        Direction direction{Direction::UP};
        if (tank.isPlayerControlled())
        {
            setPower(tank, map);
            const auto actions{Input::getGameActions()};
            const auto now{std::chrono::system_clock::now()};
            if (actions.find(InputAction::FIRE) != actions.end() &&
                tank.canFire(now))
                bullets.emplace_back(tank.fire(now));

            bool shouldMove{false};
            std::tie(shouldMove, direction) = inputActionsToDirection(actions);
            if (!shouldMove)
                continue;
        }
        else
        {
            const auto now{std::chrono::system_clock::now()};
            if (tank.canFire(now))
                bullets.emplace_back(tank.fire(now));
            const int randomDirection{distribution(randomGenerator_)};
            if (tank.getX() % Config::getInstance().getTileSize() == 0 &&
                tank.getY() % Config::getInstance().getTileSize() == 0 &&
                randomDirection < 4)
                direction = static_cast<Direction>(randomDirection);
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

bool Game::isGameEnding(const Map& map, const std::list<Tank>& tanks)
{
    if (map.isBaseDestroyed() || playerDestroyed_)
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

void Game::drawTanks(const std::list<Tank>& tanks)
{
    for (const auto& tank : tanks)
        tank.draw(screen_);
}

void Game::moveBullets(std::list<Bullet>& bullets, std::list<Tank>& tanks,
                       Map& map)
{
    for (auto bulletIter = bullets.begin(); bulletIter != bullets.end();)
    {
        bool valid{bulletIter->move()};
        if (const Point bulletCenter{bulletIter->getCenter()};
            valid && !map.canFly(bulletCenter))
        {
            map.hit(bulletCenter, bulletIter->getPower());
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

std::list<Tank>::iterator Game::hitTank(const Bullet& bullet,
                                        std::list<Tank>& tanks)
{
    return std::find_if(tanks.begin(), tanks.end(),
                        [&bullet](const auto& tank)
                        {
                            return tank.isWithin(bullet.getCenter()) &&
                                   bullet.isPlayerOrigin() !=
                                       tank.isPlayerControlled();
                        });
}

void Game::drawBullets(const std::list<Bullet>& bullets)
{
    for (const auto& bullet : bullets)
        bullet.draw(screen_);
}

void Game::draw(const std::list<Bullet>& bullets, const std::list<Tank>& tanks,
                Map& map)
{
    map.drawBackground(screen_);
    drawTanks(tanks);
    drawBullets(bullets);
    map.drawForeground(screen_);
    status_.update(getPlayerTank(tanks).getStats(), screen_);
}

void Game::setPower(Tank& tank, Map& map)
{
    if (auto [takenPowerUp, powerUp]{map.takePowerUp(tank.getCenter())};
        takenPowerUp)
        tank.applyPowerUp(powerUp);
}
