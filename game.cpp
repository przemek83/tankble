#include "game.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include "config.h"
#include "map.h"
#include "menu.h"
#include "player.h"
#include "vehicle.h"

Game::Game() { buffer = al_create_bitmap(WIDTH, HEIGHT); }
Game::~Game() { cout << "stop" << '\n'; }

void Game::movement(Vehicle* myTank, Map* mapa)
{
    int pomX = myTank->getX() / E_SIZE;
    int pomY = myTank->getY() / E_SIZE;
    int tol = 15;

    ALLEGRO_KEYBOARD_STATE key_state;
    al_get_keyboard_state(&key_state);

    //-- ustalenie kierunku --
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
    //-- jestesmy/jezdzimy po planszy --

    if (myTank->getDirectionX() == 0 && myTank->getDirectionY() != 0)
    {
        if (myTank->getY() % E_SIZE == 0)
        {
            if (myTank->getX() % E_SIZE == 0)
            { /* jest idealnie na klocku */
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
                {  // tolerancja
                    if (mapa->canDrive(pomX, pomY + myTank->getDirectionY()) &&
                        myTank->getX() % E_SIZE <= tol)
                    {
                        // przesun o kilka w lewo
                        myTank->setX(pomX * E_SIZE);
                        myTank->go();
                    }
                    else if (mapa->canDrive(pomX + 1,
                                            pomY + myTank->getDirectionY()) &&
                             myTank->getX() % E_SIZE >= E_SIZE - tol)
                    {
                        // przesun o kilka w prawo
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
            { /* jest idealnie na klocku */
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
                {  // tolerancja
                    if (mapa->canDrive(pomX + myTank->getDirectionX(), pomY) &&
                        myTank->getY() % E_SIZE <= tol)
                    {
                        // przesun o kilka w gore
                        myTank->setY(pomY * E_SIZE);
                        myTank->go();
                    }
                    else if (mapa->canDrive(pomX + myTank->getDirectionX(),
                                            pomY + 1) &&
                             myTank->getY() % E_SIZE >= E_SIZE - tol)
                    {
                        // przesun o kilka w dol
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
    this->player = new Player();
    this->mapa = new Map(player);

    std::cout << "Map loaded" << std::endl;

    ALLEGRO_EVENT_QUEUE* events{al_create_event_queue()};
    ALLEGRO_TIMER* timer{al_create_timer(1.0 / 30)};
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

        if (userWantToExit(event) || gameOver)
            break;

        if (event.type == ALLEGRO_EVENT_TIMER)
            shouldRedraw = true;

        if (shouldRedraw && al_is_event_queue_empty(events))
        {
            shouldRedraw = false;
            this->display();
            this->displayPlayer();
            this->control();
            al_flip_display();
        }
    }

    delete this->player;
    delete this->mapa;
    return 0;
}

void Game::display()
{
    /*while(!key[KEY_ESC]){*/
    /*int on = clock();
    int off;*/
    ALLEGRO_BITMAP* q1 = this->mapa->display();

    al_set_target_bitmap(al_get_backbuffer(al_get_current_display()));
    al_draw_bitmap_region(q1, 0, 0, E_SIZE * MAP_SIZE, HEIGHT, 0, 0, 0);
    //    blit(q1, screen, 0, 0, 0, 0, E_SIZE * MAP_SIZE, HEIGHT);
    /*off = clock();
    cout<<"display "
            << (static_cast<int>(off - on)) << endl;*/
    /*clwpYield();*/
    /*}*/
    // wyskocz z watkow
    /*this->gameOver = true;*/
}

void Game::displayPlayer()
{
    /*while(!key[KEY_ESC]){*/
    /*int on = clock();
    int off;*/
    ALLEGRO_BITMAP* q2 = this->player->display();
    al_set_target_bitmap(al_get_backbuffer(al_get_current_display()));
    al_draw_bitmap_region(q2, 0, 0, al_get_bitmap_width(q2),
                          al_get_bitmap_height(q2),
                          WIDTH - al_get_bitmap_width(q2), 0, 0);
    // blit(q2, screen, 0, 0, E_SIZE * MAP_SIZE, 0, WIDTH - E_SIZE * MAP_SIZE,
    //     HEIGHT);
    /*off = clock();
    cout<<"displayPlayer "
            << (static_cast<int>(off - on)) << endl;*/
    /*clwpYield();*/
    /*}*/
    // wyskocz z watkow
    /*this->gameOver = true;*/
}

void Game::control()
{
    /*clear_keybuf();*/
    Vehicle* tank;
    /*while(!key[KEY_ESC]){*/
    try
    {
        /*int on = clock();
        int off;*/
        if (mapa->vehicles.size() == 1)
        {
            throw Win();
        }
        for (uint i = 0; i < mapa->vehicles.size(); i++)
        {
            tank = mapa->vehicles.at(i);
            if (tank->getId() >= 100 && tank->getId() < 200)
            {
                ALLEGRO_KEYBOARD_STATE key_state;
                al_get_keyboard_state(&key_state);

                if (al_key_down(&key_state, ALLEGRO_KEY_UP) ||
                    al_key_down(&key_state, ALLEGRO_KEY_DOWN) ||
                    al_key_down(&key_state, ALLEGRO_KEY_LEFT) ||
                    al_key_down(&key_state, ALLEGRO_KEY_RIGHT))
                {
                    // dla czolgu gracza
                    this->movement(tank, mapa);
                }
                if (al_key_down(&key_state, ALLEGRO_KEY_SPACE) ||
                    al_key_down(&key_state, ALLEGRO_KEY_ENTER))
                {
                    tank->fire(mapa);
                }
            }
            else
            {  // komputer
                tank->moveRandom(mapa);
                tank->fire(mapa);
            }
        }
        // obsluga pocisku
        mapa->moveBullet();
        // wskocz do nastepnego watku
        /*off = clock();
        cout<<"control " << (static_cast<int>(off - on)) << endl;*/
        /*clwpYield();*/
    }
    catch (Win& ex)
    {
        /*clwpThreadSuspend( this->ids[1] );
        clwpThreadSuspend( this->ids[2] );*/
        /* przegrales */
        ex.display();
        this->gameOver = true;
    }
    catch (Lose& ex)
    {
        /*clwpThreadSuspend( this->ids[1] );
        clwpThreadSuspend( this->ids[2] );*/
        /* wygrales */
        ex.display();
        this->gameOver = true;
    }
    /*}*/
    // wyskocz z watkow
    /*this->gameOver = true;*/
}
