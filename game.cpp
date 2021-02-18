#include "game.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include "config.h"
#include "map.h"
#include "menu.h"
#include "player.h"
#include "vehicle.h"
//#include "clwp/clwp.h"

Game::Game()
{
    //    cout << "start"
    //         << "\n";

    //    ALLEGRO_DISPLAY* display = NULL;

    //    if (!al_init())
    //    {
    //        fprintf(stderr, "failed to initialize allegro!\n");
    //        return;
    //    }

    //    al_install_keyboard();

    //    // al_set_new_display_flags(ALLEGRO_FULLSCREEN);
    //    al_set_new_display_option(ALLEGRO_COLOR_SIZE, 32, ALLEGRO_REQUIRE);

    //    bool fullscreen = false;
    //    if (fullscreen)
    //    {
    //        al_set_new_display_flags(ALLEGRO_FULLSCREEN);
    //    }

    //    display = al_create_display(WIDTH, HEIGHT);
    //    if (!display)
    //    {
    //        fprintf(stderr, "failed to create display!\n");
    //        return;
    //    }

    //    //    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    //    //    if (!queue)
    //    //    {
    //    //        printf("failed to create queue\n");
    //    //    }

    //    //    al_register_event_source(queue, al_get_keyboard_event_source());
    //    //    al_register_event_source(queue,
    //    al_get_display_event_source(display));

    //    al_clear_to_color(al_map_rgb(0, 0, 0));
    //    al_flip_display();

    //    al_init_image_addon();
    //    al_init_font_addon();

    //    //    bool quit = false;
    //    //    do
    //    //    {
    //    //        al_clear_to_color(al_map_rgb(0, 0, 0));
    //    //        al_flip_display();

    //    //        do
    //    //        {
    //    //            ALLEGRO_EVENT ev;
    //    //            al_wait_for_event(queue, &ev);

    //    //            if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
    //    //            {
    //    //                quit = true;
    //    //            }
    //    //            if ((ev.type == ALLEGRO_EVENT_KEY_DOWN) &&
    //    //                (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE))
    //    //            {
    //    //                quit = true;
    //    //            }
    //    //            if ((ev.type == ALLEGRO_EVENT_KEY_DOWN) &&
    //    //                (ev.keyboard.keycode == ALLEGRO_KEY_F))
    //    //            {
    //    //                fullscreen = !fullscreen;
    //    //                al_toggle_display_flag(display,
    //    ALLEGRO_FULLSCREEN_WINDOW,
    //    //                                       fullscreen);
    //    //            }

    //    //        } while (!al_is_event_queue_empty(queue));
    //    //    } while (!quit);

    //    // al_init();
    //    al_set_window_title(al_get_current_display(), "TankBle");
    //    // al_install_keyboard();
    //    al_install_mouse();
    //    // set_color_depth(16);
    //    // 0,0 is set for virtual screen, 0,0 for disable
    //    // windowedScreen();
    //    // set_gfx_mode(GFX_AUTODETECT, WIDTH, HEIGHT, 0, 0);
    //    // PALETTE palette;
    //    // set_palette(palette);

    //    // important -> buffer
    buffer = al_create_bitmap(WIDTH, HEIGHT);
    //    al_hide_mouse_cursor(al_get_current_display());

    //    //    cursor_x = WIDTH / 2;
    //    //    cursor_y = HEIGHT / 2;
    //    // createMenu();
}
Game::~Game()
{
    al_uninstall_mouse();
    al_uninstall_keyboard();
    cout << "stop" << '\n';
    // allegro_exit();
}

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

// ******************************* MENU **********************************

// void Game::createMenu()
//{
//    Menu* menu = new Menu(WIDTH, HEIGHT);
//    menu->addItem(new Item(&Game::createMenuNew, "NEW GAME"));
//    menu->addItem(new Item(&Game::createMenuLoad, "LOAD LEVEL"));
//    menu->addItem(new Item(&Game::createMenuOptions, "OPTIONS"));
//    menu->addItem(new Item(&Game::endMenu, "EXIT", true));
//    menu->loop(buffer, this);
//}

// int Game::createMenuNew()
//{
//    Menu* m = new Menu(WIDTH, HEIGHT);
//    // value "true" for exit from current menu
//    m->addItem(new Item(&Game::startGame, "LOCAL GAME"));
//    m->addItem(new Item(&Game::createMenuGame, "NETWORK GAME"));
//    m->addItem(new Item(&Game::endMenu, "BACK", true));
//    return m->loop(buffer, this);
//}

// int Game::createMenuGame()
//{
//    Menu* m = new Menu(WIDTH, HEIGHT);
//    m->addItem(new Item(&Game::endMenu, "(SERVER) CREATE SERVER"));
//    m->addItem(new Item(&Game::endMenu, "(CLIENT) CONNECT TO SERVER"));
//    m->addItem(new Item(&Game::endMenu, "BACK", true));
//    return m->loop(buffer, this);
//}
// int Game::createMenuLoad()
//{
//    Menu* m = new Menu(WIDTH, HEIGHT);
//    // value "true" for exit from current menu
//    m->addItem(new Item(&Game::endMenu, "BACK LOAD", true));
//    return m->loop(buffer, this);
//}

// int Game::createMenuOptions()
//{
//    Menu* m = new Menu(WIDTH, HEIGHT);
//    // value "true" for exit from current menu
//    m->addItem(new Item(&Game::fullScreen, "FULLSCREEN MODE", false));
//    m->addItem(new Item(&Game::windowedScreen, "WINDOWED MODE", false));
//    m->addItem(new Item(&Game::endMenu, "BACK OPTIONS", true));
//    return m->loop(buffer, this);
//}

// int Game::endMenu() { return 0; }

int Game::fullScreen()
{
    al_set_new_display_flags(ALLEGRO_FULLSCREEN);
    return 0;  // set_gfx_mode(GFX_AUTODETECT, WIDTH, HEIGHT, 0, 0);
}

int Game::windowedScreen()
{
    al_set_new_display_flags(ALLEGRO_WINDOWED);
    //    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, WIDTH, HEIGHT, 0, 0) != 0)
    //    {
    //        return set_gfx_mode(GFX_AUTODETECT, WIDTH, HEIGHT, 0, 0);
    //    }
    return 0;
}

int Game::startGame()
{
    this->player = new Player();
    this->mapa = new Map(player);
    // al_hide_mouse_cursor(al_get_current_display());

    /*if(clwpInit(1)){
            this->ids[0] = clwpSpawn(controlz, this, 4096, 1, true);
            this->ids[1] = clwpSpawn(displayz, this, 4096, 1, true);
            this->ids[2] = clwpSpawn(displayPlayerz, this, 4096, 1, true);

            this->gameOver = false;
            while(!this->gameOver){
                    int on = clock();
                    int off;
                    clwpYield();
                    off = clock();
                    cout<<"loop all " << (static_cast<int>(off - on)) << endl;
            }


            clwpKill(this->ids[0]);
            clwpKill(this->ids[1]);
            clwpKill(this->ids[2]);
    }*/

    std::cout << "Map loaded" << std::endl;
    this->gameOver = false;
    ALLEGRO_KEYBOARD_STATE key_state;
    al_get_keyboard_state(&key_state);

    while (!this->gameOver && !al_key_down(&key_state, ALLEGRO_KEY_ESCAPE))
    {
        /*int on = clock();
        int off;*/

        this->display();
        this->displayPlayer();
        this->control();
        al_flip_display();
        al_rest(1.0 / 30);

        /*off = clock();
        cout<<"loop all " << (static_cast<int>(off - on)) << endl;*/
    }

    std::cout << "Game ended" << std::endl;

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

void controlz(void* obj)
{
    Game* g = (Game*)obj;
    g->control();
}

void displayz(void* obj)
{
    Game* g = (Game*)obj;
    g->display();
}

void displayPlayerz(void* obj)
{
    Game* g = (Game*)obj;
    g->displayPlayer();
}
