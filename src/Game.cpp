#include "../Headers/pch.h"
#include "../Headers/Game.hpp"

game::game()
    : grid_size(50.f)
{
    // Order!!
    gfx.load_from_file("../Config/window.ini");
    init_window();
    init_keys();
    init_state_data();
    init_states();
}

/* Initializer functions */
void game::init_window()
{
    if (gfx.fullscreen)
        window = new sf::RenderWindow(gfx.resolution, gfx.title, sf::Style::Fullscreen, gfx.cs);
    else
        window = new sf::RenderWindow(gfx.resolution, gfx.title, sf::Style::Titlebar | sf::Style::Close, gfx.cs);

    window->setFramerateLimit(gfx.framerate_limit);
    window->setVerticalSyncEnabled(gfx.vsync);
}

void game::init_state_data()
{
    state_details.window = this->window;
    state_details.gfx_settings = &this->gfx;
    state_details.supported_keys = &this->supported_keys;
    state_details.states = &this->states;
    state_details.grid_size = this->grid_size;
}

void game::init_keys()
{
    std::ifstream ifs;
    ifs.open("../Config/supported_keys.ini", std::ios::in);
    if (ifs.is_open())
    {
        std::string key = "";
        int key_value = 0;
        while (ifs >> key >> key_value)
        {
            supported_keys[key] = key_value;
        }
    }
    ifs.close();
}

void game::init_states()
{
    states.push(new main_menu_state(&state_details));
}

/* Update */
void game::update()
{
    if (!states.empty())
    {
        states.top()->update(dt);
        if (states.top()->get_quit())
        {
            states.top()->end_state();
            delete states.top();
            states.pop();
        }
    }
    else
    {
        exit_window();
        window->close();
    }
}

void game::update_sfml_events()
{
    while (window->pollEvent(event))
        if (event.type == sf::Event::Closed)
            window->close();

}

void game::update_delta_time()
{
    dt = dt_clock.restart().asSeconds();
}

/* Render */
void game::render()
{
    window->clear();

    if (!states.empty())
        states.top()->render(window);

    window->display();
}

void game::run()
{
    while (window->isOpen())
    {
        update_delta_time();
        update_sfml_events();
        update();
        render();
    }
}

void game::exit_window()
{
    std::cout << "Closing main window\n";
}

game::~game()
{
    delete window;

    while (!states.empty())
    {
        delete states.top();
        states.pop();
    }
}