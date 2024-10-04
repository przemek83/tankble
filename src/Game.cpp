#include "Game.h"

#include <algorithm>
#include <chrono>
#include <fstream>
#include <thread>

#include "Bullet.h"
#include "Config.h"
#include "Display.h"
#include "InputAction.h"
#include "Level.h"
#include "Map.h"
#include "MapUtils.h"
#include "PointUtils.h"
#include "Resources.h"
#include "StandardInput.h"
#include "Tank.h"
#include "Utils.h"

Game::Game(Display& display)
    : status_{{Config::getInstance().getBoardWidth(), 0}},
      randomGenerator_{Config::getRandomSeed()},
      display_{display},
      map_{Config::getInstance().getTileCount()}
{
}

bool Game::init(Level level)
{
    auto [success, levelContent]{Resources::getLevel(level)};
    if (!success)
        return false;

    tanks_ = map_.loadMap(levelContent);
    levelContent.close();

    display_.clearScreenWithBlack();

    return true;
}

bool Game::play(Input& input)
{
    std::list<Bullet> bullets;
    while (true)
    {
        const InputAction action{input.getMenuAction()};
        if ((action == InputAction::BACK) || (isGameEnding()))
            break;

        if (action == InputAction::QUIT)
            return false;

        if (action == InputAction::TIMER)
        {
            draw(bullets);
            control(bullets);
            display_.refresh();
        }
    }

    return true;
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

const Tank& Game::getPlayerTank()
{
    const auto& playerTankIter =
        std::find_if(tanks_.cbegin(), tanks_.cend(), [](const auto& tank)
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

void Game::control(std::list<Bullet>& bullets)
{
    moveBullets(bullets);

    StandardInput input;
    for (auto& tank : tanks_)
    {
        Direction direction{Direction::UP};
        if (tank.isPlayerControlled())
        {
            setPower(tank);
            const auto actions{input.getGameActions()};
            const auto now{std::chrono::system_clock::now()};
            if ((actions.find(InputAction::FIRE) != actions.end()) &&
                tank.canFire(now))
                bullets.emplace_back(tank.fire(now));

            const int tileSize{Config::getInstance().getTileSize()};
            map_.tagAreaAsChanged(tank.getLocation(), {tank.getX() + tileSize,
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
            if (((tank.getX() % Config::getInstance().getTileSize()) == 0) &&
                ((tank.getY() % Config::getInstance().getTileSize()) == 0) &&
                (randomDirection < 4))
                direction = static_cast<Direction>(randomDirection);
            else
                direction = tank.getDirection();
        }
        movement(tank, direction);
    }
}

void Game::drawEndOfGame(const std::string& text) const
{
    display_.clearScreenWithBlack();
    display_.drawText(
        utils::getMidpoint(Config::getInstance().getBoardWidth() +
                           Config::getInstance().getSatusWidth()),
        utils::getMidpoint(Config::getInstance().getBoardHeight()), text);
    display_.refresh();
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

bool Game::isGameEnding() const
{
    if (map_.isBaseDestroyed() || playerDestroyed_)
    {
        drawEndOfGame("You loose");
        return true;
    }

    if (tanks_.size() == 1)
    {
        drawEndOfGame("You Win");
        return true;
    }

    return false;
}

void Game::drawTanks() const
{
    for (const auto& tank : tanks_)
        tank.draw(display_);
}

void Game::moveBullets(std::list<Bullet>& bullets)
{
    const int bulletSize{Config::getInstance().getBulletSize()};
    const int tileSize{Config::getInstance().getTileSize()};
    for (auto bulletIter = bullets.begin(); bulletIter != bullets.end();)
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
        bulletIter = (valid ? ++bulletIter : bullets.erase(bulletIter));
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

void Game::drawBullets(const std::list<Bullet>& bullets) const
{
    for (const auto& bullet : bullets)
        bullet.draw(display_);
}

void Game::draw(const std::list<Bullet>& bullets)
{
    map_.drawBackground(display_);
    drawTanks();
    drawBullets(bullets);
    map_.drawForeground(display_);
    status_.update(getPlayerTank().getStats(), display_);
}

void Game::setPower(Tank& tank)
{
    if (auto [takenPowerUp, powerUp]{map_.takePowerUp(tank.getCenter())};
        takenPowerUp)
        tank.applyPowerUp(powerUp);
}
