#include "game.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include "config.h"
#include "map.h"
#include "menu.h"
#include "player.h"
#include "vehicle.h"

Game::Game() { buffer_ = al_create_bitmap(WIDTH, HEIGHT); }
Game::~Game() { cout << "stop" << '\n'; }

void Game::movement(Vehicle* myTank, Map* mapa)
{
    int pomX = myTank->getX() / E_SIZE;
    int pomY = myTank->getY() / E_SIZE;
    int tol = 15;

    ALLEGRO_KEYBOARD_STATE key_state;
    al_get_keyboard_state(&key_state);

    if (al_key_down(&key_state, ALLEGRO_KEY_UP))
    {
        myTank->move(0);
    }
    else if (al_key_down(&key_state, ALLEGRO_KEY_DOWN))
    {
        myTank->move(2);
    }
    else if (al_key_down(&key_state, ALLEGRO_KEY_LEFT))
    {
        myTank->move(3);
    }
    else if (al_key_down(&key_state, ALLEGRO_KEY_RIGHT))
    {
        myTank->move(1);
    }
    if (!mapa->isValid(
            myTank->getX() + myTank->getDirectionX() + myTank->getDirectionX(),
            myTank->getY() + myTank->getDirectionY() + myTank->getDirectionY()))
    {
        return;
    }

    if (myTank->getDirectionX() == 0 && myTank->getDirectionY() != 0)
    {
        if (myTank->getY() % E_SIZE == 0)
        {
            if (myTank->getX() % E_SIZE == 0)
            {
                if (mapa->canDrive(pomX, pomY + myTank->getDirectionY()))
                {
                    myTank->go();
                }
            }
            else
            {
                if (mapa->canDrive(pomX, pomY + myTank->getDirectionY()) &&
                    mapa->canDrive(pomX + 1, pomY + myTank->getDirectionY()))
                {
                    myTank->go();
                }
                else
                {
                    if (mapa->canDrive(pomX, pomY + myTank->getDirectionY()) &&
                        myTank->getX() % E_SIZE <= tol)
                    {
                        myTank->setX(pomX * E_SIZE);
                        myTank->go();
                    }
                    else if (mapa->canDrive(pomX + 1,
                                            pomY + myTank->getDirectionY()) &&
                             myTank->getX() % E_SIZE >= E_SIZE - tol)
                    {
                        myTank->setX((pomX + 1) * E_SIZE);
                        myTank->go();
                    }
                }
            }
        }
        else
        {
            myTank->go();
        }
    }
    else if (myTank->getDirectionY() == 0 && myTank->getDirectionX() != 0)
    {
        if (myTank->getX() % E_SIZE == 0)
        {
            if (myTank->getY() % E_SIZE == 0)
            {
                if (mapa->canDrive(pomX + myTank->getDirectionX(), pomY))
                {
                    myTank->go();
                }
            }
            else
            {
                if (mapa->canDrive(pomX + myTank->getDirectionX(), pomY) &&
                    mapa->canDrive(pomX + myTank->getDirectionX(), pomY + 1))
                {
                    myTank->go();
                }
                else
                {
                    if (mapa->canDrive(pomX + myTank->getDirectionX(), pomY) &&
                        myTank->getY() % E_SIZE <= tol)
                    {
                        myTank->setY(pomY * E_SIZE);
                        myTank->go();
                    }
                    else if (mapa->canDrive(pomX + myTank->getDirectionX(),
                                            pomY + 1) &&
                             myTank->getY() % E_SIZE >= E_SIZE - tol)
                    {
                        myTank->setY((pomY + 1) * E_SIZE);
                        myTank->go();
                    }
                }
            }
        }
        else
        {
            myTank->go();
        }
    }
    mapa->setPower(myTank);
}

bool Game::userWantToExit(const ALLEGRO_EVENT& event) const
{
    return event.type == ALLEGRO_EVENT_DISPLAY_CLOSE ||
           (event.type == ALLEGRO_EVENT_KEY_UP &&
            event.keyboard.keycode == ALLEGRO_KEY_ESCAPE);
}

int Game::startGame()
{
    player_ = new Player();
    map_ = new Map(player_);

    std::cout << "Map loaded" << std::endl;

    ALLEGRO_EVENT_QUEUE* events{al_create_event_queue()};
    ALLEGRO_TIMER* timer{al_create_timer(1.0 / Config::fps)};
    al_register_event_source(events, al_get_keyboard_event_source());
    al_register_event_source(events, al_get_mouse_event_source());
    al_register_event_source(
        events, al_get_display_event_source(al_get_current_display()));
    al_register_event_source(events, al_get_timer_event_source(timer));
    al_start_timer(timer);

    bool shouldRedraw{true};

    while (true)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(events, &event);

        if (userWantToExit(event) || gameOver_)
            break;

        if (event.type == ALLEGRO_EVENT_TIMER)
            shouldRedraw = true;

        if (shouldRedraw && al_is_event_queue_empty(events))
        {
            shouldRedraw = false;
            display();
            displayPlayer();
            control();
            al_flip_display();
        }
    }

    delete player_;
    delete map_;
    return 0;
}

void Game::display()
{
    ALLEGRO_BITMAP* q1 = map_->display();
    al_set_target_bitmap(al_get_backbuffer(al_get_current_display()));
    al_draw_bitmap_region(q1, 0, 0, E_SIZE * MAP_SIZE, HEIGHT, 0, 0, 0);
}

void Game::displayPlayer()
{
    ALLEGRO_BITMAP* q2 = player_->display();
    al_set_target_bitmap(al_get_backbuffer(al_get_current_display()));
    al_draw_bitmap_region(q2, 0, 0, al_get_bitmap_width(q2),
                          al_get_bitmap_height(q2),
                          WIDTH - al_get_bitmap_width(q2), 0, 0);
}

void Game::control()
{
    try
    {
        if (map_->vehicles.size() == 1)
        {
            throw Win();
        }
        for (uint i = 0; i < map_->vehicles.size(); i++)
        {
            Vehicle* tank = map_->vehicles.at(i);
            if (tank->getId() >= 100 && tank->getId() < 200)
            {
                ALLEGRO_KEYBOARD_STATE key_state;
                al_get_keyboard_state(&key_state);

                if (al_key_down(&key_state, ALLEGRO_KEY_UP) ||
                    al_key_down(&key_state, ALLEGRO_KEY_DOWN) ||
                    al_key_down(&key_state, ALLEGRO_KEY_LEFT) ||
                    al_key_down(&key_state, ALLEGRO_KEY_RIGHT))
                {
                    movement(tank, map_);
                }
                if (al_key_down(&key_state, ALLEGRO_KEY_SPACE) ||
                    al_key_down(&key_state, ALLEGRO_KEY_ENTER))
                {
                    tank->fire(map_);
                }
            }
            else
            {
                tank->moveRandom(map_);
                tank->fire(map_);
            }
        }

        map_->moveBullet();
    }
    catch (Win& ex)
    {
        ex.display();
        gameOver_ = true;
    }
    catch (Lose& ex)
    {
        ex.display();
        gameOver_ = true;
    }
}
