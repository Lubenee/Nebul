#include "../Headers/pch.h"
#include "../Headers/GameState.hpp"

game_state::game_state(state_data *_state_data)
    : state(_state_data)
{
    init_keybinds();
    init_assets();
    init_player();
    init_pause_menu();
    init_map();
}

void game_state::init_pause_menu()
{
    p_menu = new pause_menu(*window, p_menu_font);
}

void game_state::init_map()
{
    map = new tilemap(state_details->grid_size, 10, 10);
}

void game_state::init_player()
{
    plr = new player(0, 0, textures["PLAYER_SHEET"]);
}

void game_state::init_assets()
{
    if (!textures["PLAYER_SHEET"].loadFromFile("../Assets/Images/Player/PLAYER_SHEET.png"))
        throw("ERROR::GAME_STATE_H::INIT_TEXTURES::FAILED TO LOAD PLAYER TEXTURE SHEET");
    if (!p_menu_font.loadFromFile("../Fonts/pixelfont.TTF"))
        throw("ERROR::MAIN_MENU_STATE_H::COULD NOT LOAD FONT");
}

void game_state::init_keybinds()
{
    std::ifstream ifs;
    ifs.open("../Config/gamestate_keybinds.ini", std::ios::in);
    if (ifs.is_open())
    {
        std::string key = "";
        std::string key_value = "";
        while (ifs >> key >> key_value)
            keybinds[key] = supported_keys->at(key_value);
    }
    ifs.close();
}

void game_state::update_menu_buttons()
{
    if (p_menu->is_button_pressed("QUIT"))
        end_state();
}

void game_state::update_input(const float &dt)
{
    update_mouse_pos();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds["PAUSE"])) && pressable_button())
        paused == false ? set_pause(true) : set_pause(false);
}

void game_state::update(const float &dt)
{
    update_input(dt);

    if (!paused)
    {
        plr->update(dt);
        update_player_input(dt);
    }
    else if (paused)
    {
        p_menu->update(mouse_pos_view);
        update_menu_buttons();
    }
}

void game_state::update_player_input(const float &dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds["MOVE_LEFT"])))
        plr->move(-1.f, 0.f, dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds["MOVE_RIGHT"])))
        plr->move(1.f, 0.f, dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds["MOVE_UP"])))
        plr->move(0.f, -1.f, dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds["MOVE_DOWN"])))
        plr->move(0.f, 1.f, dt);
}

void game_state::render(sf::RenderTarget *target)
{
    if (!target)
        target = window;

    // map->render(*target);

    plr->render(*target);

    if (paused)
        p_menu->render(*target);
}

game_state::~game_state()
{
    delete map;
    delete p_menu;
    delete plr;
}