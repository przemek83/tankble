#include "Game.h"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <thread>

#include "Bullet.h"
#include "Config.h"
#include "Display.h"
#include "InputAction.h"
#include "Map.h"
#include "MapUtils.h"
#include "PointUtils.h"
#include "Tank.h"
#include "Utils.h"

Game::Game()
    : status_{{Config::getInstance().getBoardWidth(), 0}},
      randomGenerator_{Config::getRandomSeed()},
      map_{Config::getInstance().getTileCount()}
{
}

void Game::init(std::iostream& level) { tanks_ = map_.loadMap(level); }

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

Tank& Game::getPlayerTank()
{
    auto playerTankIter =
        std::find_if(tanks_.begin(), tanks_.end(), [](const auto& tank)
                     { return tank.isPlayerControlled(); });
    return *playerTankIter;
}

void Game::movement(Tank& tank, Direction direction)
{
    tank.setDirection(direction);

    const int tileSize{Config::getInstance().getTileSize()};
    map_.tagAreaAsChanged(tank.getLocation(),
                          {tank.getX() + tileSize, tank.getY() + tileSize});

    auto [newX, newY]{tank.getNextExpectedPosition()};
    if (!point_utils::isValidPoint(newX, newY, tileSize))
        return;

    Point newPoint{newX, newY};
    const std::vector<Point> pointsToCheck{
        map_utils::getMovePoints(newPoint, direction, tileSize)};
    if (std::all_of(pointsToCheck.cbegin(), pointsToCheck.cend(),
                    [&map = map_](Point point) { return map.canDrive(point); }))
    {
        if (tank.isPlayerControlled())
            map_.shift(newPoint, direction);
        tank.move(newPoint);
        map_.tagAreaAsChanged(tank.getLocation(),
                              {tank.getX() + tileSize, tank.getY() + tileSize});
    }
}

void Game::movePlayerTank(const std::set<InputAction>& actions)
{
    Tank& tank{getPlayerTank()};

    Direction direction{Direction::UP};
    setPower(tank);
    const auto now{std::chrono::system_clock::now()};
    if ((actions.find(InputAction::FIRE) != actions.end()) && tank.canFire(now))
        bullets_.emplace_back(tank.fire(now));

    const int tileSize{Config::getInstance().getTileSize()};
    map_.tagAreaAsChanged(tank.getLocation(),
                          {tank.getX() + tileSize, tank.getY() + tileSize});

    bool shouldMove{false};
    std::tie(shouldMove, direction) = inputActionsToDirection(actions);
    if (shouldMove)
        movement(tank, direction);
}

void Game::moveEnemyTanks()
{
    for (auto& tank : tanks_)
    {
        if (!tank.isPlayerControlled())
        {
            Direction direction{Direction::UP};
            const auto now{std::chrono::system_clock::now()};
            if (tank.canFire(now))
                bullets_.emplace_back(tank.fire(now));
            const int randomDirection{distribution_(randomGenerator_)};
            if (((tank.getX() % Config::getInstance().getTileSize()) == 0) &&
                ((tank.getY() % Config::getInstance().getTileSize()) == 0) &&
                (randomDirection < 4))
                direction = static_cast<Direction>(randomDirection);
            else
                direction = tank.getDirection();
            movement(tank, direction);
        }
    }
}

void Game::drawEndOfGame(Display& display, const std::string& text) const
{
    display.clearScreenWithBlack();
    display.drawText(utils::getMidpoint(Config::getInstance().getBoardWidth() +
                                        Config::getInstance().getSatusWidth()),
                     utils::getMidpoint(Config::getInstance().getBoardHeight()),
                     text);
    display.refresh();
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

bool Game::isGameEnding(Display& display) const
{
    if (map_.isBaseDestroyed() || playerDestroyed_)
    {
        drawEndOfGame(display, "You loose");
        return true;
    }

    if (tanks_.size() == 1)
    {
        drawEndOfGame(display, "You Win");
        return true;
    }

    return false;
}

void Game::drawTanks(Display& display) const
{
    for (const auto& tank : tanks_)
        tank.draw(display);
}

void Game::moveBullets()
{
    const int bulletSize{Config::getInstance().getBulletSize()};
    const int tileSize{Config::getInstance().getTileSize()};
    for (auto bulletIter = bullets_.begin(); bulletIter != bullets_.end();)
    {
        map_.tagAreaAsChanged(
            bulletIter->getLocation(),
            {bulletIter->getX() + bulletSize, bulletIter->getY() + bulletSize});
        bool valid{bulletIter->move()};
        map_.tagAreaAsChanged(
            bulletIter->getLocation(),
            {bulletIter->getX() + bulletSize, bulletIter->getY() + bulletSize});
        if (const Point bulletCenter{bulletIter->getCenter()};
            valid && (!map_.canFly(bulletCenter)))
        {
            map_.hit(bulletCenter, bulletIter->getPower());
            valid = false;
        }

        if (auto tankIter{hitTank(*bulletIter)};
            valid && (tankIter != tanks_.end()))
        {
            map_.tagAreaAsChanged(
                tankIter->getLocation(),
                {tankIter->getX() + tileSize, tankIter->getY() + tileSize});

            if (tankIter->hit(bulletIter->getPower()))
            {
                if (tankIter->isPlayerControlled())
                    playerDestroyed_ = true;
                tanks_.erase(tankIter);
            }
            valid = false;
        }
        bulletIter = (valid ? ++bulletIter : bullets_.erase(bulletIter));
    }
}

std::list<Tank>::iterator Game::hitTank(const Bullet& bullet)
{
    return std::find_if(
        tanks_.begin(), tanks_.end(),
        [&bullet](const auto& tank)
        {
            return tank.isWithin(bullet.getCenter()) &&
                   (bullet.isPlayerOrigin() != tank.isPlayerControlled());
        });
}

void Game::drawBullets(Display& display) const
{
    for (const auto& bullet : bullets_)
        bullet.draw(display);
}

void Game::draw(Display& display)
{
    map_.drawBackground(display);
    drawTanks(display);
    drawBullets(display);
    map_.drawForeground(display);
    status_.update(getPlayerTank().getStats(), display);
}

void Game::setPower(Tank& tank)
{
    if (auto [takenPowerUp, powerUp]{map_.takePowerUp(tank.getCenter())};
        takenPowerUp)
        tank.applyPowerUp(powerUp);
}
