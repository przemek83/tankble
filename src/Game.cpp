#include "Game.h"

#include <algorithm>
#include <chrono>
#include <fstream>
#include <thread>

#include "Bullet.h"
#include "Config.h"
#include "Input.h"
#include "InputAction.h"
#include "Level.h"
#include "Map.h"
#include "MapUtils.h"
#include "PointUtils.h"
#include "Screen.h"
#include "Tank.h"

Game::Game(Screen& screen)
    : status_({Config::getInstance().getBoardWidth(), 0}),
      randomGenerator_(Config::getRandomSeed()),
      screen_(screen),
      distribution_(std::uniform_int_distribution<>(0, 7))
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
    const auto& playerTankIter =
        std::find_if(tanks.begin(), tanks.end(), [](const auto& tank)
                     { return tank.isPlayerControlled(); });
    return *playerTankIter;
}

void Game::movement(Tank& tank, Map& map, Direction direction)
{
    const unsigned int tileSize{Config::getInstance().getTileSize()};
    tank.setDirection(direction);

    map.tagAreaAsChanged(tank.getLocation(),
                         {tank.getX() + tileSize, tank.getY() + tileSize});

    auto [newX, newY]{tank.getNextExpectedPosition()};
    if (!point_utils::isValidPoint(newX, newY, tileSize))
        return;

    Point newPoint{static_cast<unsigned int>(newX),
                   static_cast<unsigned int>(newY)};
    const std::vector<Point> pointsToCheck{
        map_utils::getMovePoints(newPoint, direction, tileSize)};
    if (std::all_of(pointsToCheck.cbegin(), pointsToCheck.cend(),
                    [&map](Point point) { return map.canDrive(point); }))
    {
        if (tank.isPlayerControlled())
            map.shift(newPoint, direction);
        tank.move(newPoint);
        map.tagAreaAsChanged(tank.getLocation(),
                             {tank.getX() + tileSize, tank.getY() + tileSize});
    }
}

bool Game::play(Level level)
{
    Map map(Config::getInstance().getTileCount());
    std::fstream levelContent{Resources::getLevel(level)};
    std::list<Tank> tanks{map.loadMap(levelContent)};
    levelContent.close();

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

            const unsigned int tileSize{Config::getInstance().getTileSize()};
            map.tagAreaAsChanged(tank.getLocation(), {tank.getX() + tileSize,
                                                      tank.getY() + tileSize});

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
            const int randomDirection{distribution_(randomGenerator_)};
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
    const unsigned int bulletSize{Config::getInstance().getBulletSize()};
    const unsigned int tileSize{Config::getInstance().getTileSize()};
    for (auto bulletIter = bullets.begin(); bulletIter != bullets.end();)
    {
        map.tagAreaAsChanged(
            bulletIter->getLocation(),
            {bulletIter->getX() + bulletSize, bulletIter->getY() + bulletSize});
        bool valid{bulletIter->move()};
        map.tagAreaAsChanged(
            bulletIter->getLocation(),
            {bulletIter->getX() + bulletSize, bulletIter->getY() + bulletSize});
        if (const Point bulletCenter{bulletIter->getCenter()};
            valid && !map.canFly(bulletCenter))
        {
            map.hit(bulletCenter, bulletIter->getPower());
            valid = false;
        }

        if (auto tankIter{hitTank(*bulletIter, tanks)};
            valid && tankIter != tanks.end())
        {
            map.tagAreaAsChanged(
                tankIter->getLocation(),
                {tankIter->getX() + tileSize, tankIter->getY() + tileSize});

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
