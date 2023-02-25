#include "../Headers/pch.h"
#include "../Headers/GameState.hpp"

game_state::game_state(state_data *_state_data)
    : state(_state_data)
{
    init_keybinds();
    init_assets();
    init_player();
    init_player_gui();
    init_pause_menu();
    init_map();
    init_view();
    init_render_canvas();
    init_shaders();
}

void game_state::init_shaders()
{
    if (!core_shader.loadFromFile("../Shaders/vertex_shader.vert", "../Shaders/fragment_shader.frag"))
        throw("ERROR::GAME_STATE::FAILED TO LOAD SHADERS.\n");
}

void game_state::init_player_gui()
{
    plr_gui = new player_gui(plr, state_details->gfx_settings->resolution);
}

void game_state::init_render_canvas()
{
    render_texture.create(
        state_details->gfx_settings->resolution.width,
        state_details->gfx_settings->resolution.height);

    render_sprite.setTexture(render_texture.getTexture());
    render_sprite.setTextureRect(sf::IntRect(0, 0, state_details->gfx_settings->resolution.width,
                                             state_details->gfx_settings->resolution.height));
}

void game_state::init_view()
{
    view.setSize(
        state_details->gfx_settings->resolution.width,
        state_details->gfx_settings->resolution.height);

    view.setCenter(
        state_details->gfx_settings->resolution.width / 2.f,
        state_details->gfx_settings->resolution.height / 2.f);
}

void game_state::init_pause_menu()
{
    const sf::VideoMode &vm = state_details->gfx_settings->resolution;
    p_menu = new pause_menu(state_details->gfx_settings->resolution, p_menu_font);

    p_menu->add_button("QUIT", GUI::p2p_y(85, vm), GUI::p2p_x(15.f, vm), GUI::p2p_y(6.4f, vm), GUI::calc_char_size(vm), "Quit");
}

void game_state::init_map()
{
    map = new tilemap(state_details->grid_size, 100, 100, "../Assets/tiles/tilesheet3.png");
    map->load_tilemap("savefile.sav");
}

void game_state::init_player()
{
    plr = new player(0, 0, textures["PLAYER_SHEET"]);
}

void game_state::init_assets()
{
    if (!textures["PLAYER_SHEET"].loadFromFile("../Assets/Images/Player/PLAYER_SHEET2.png"))
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
    update_mouse_pos(&view);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds["PAUSE"])) && pressable_button())
        paused == false ? set_pause(true) : set_pause(false);
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::K) && pressable_button())
        plr->lose_hp(1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::I) && pressable_button())
        plr->gain_hp(1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        plr->gain_exp(10);
}

void game_state::update_player_gui(const float &dt)
{
    plr_gui->update(dt);
}

void game_state::update_view(const float &dt)
{
    /* std::floor is used in order to fix line tearing while rendering. That way the player.pos values are a bit more precise. */
    view.setCenter(
        std::floor(plr->get_pos().x + (static_cast<float>(mouse_pos_window.x) - static_cast<float>(state_details->gfx_settings->resolution.width / 2)) / 6.f),
        std::floor(plr->get_pos().y + (static_cast<float>(mouse_pos_window.y) - static_cast<float>(state_details->gfx_settings->resolution.height / 2)) / 6.f));
}

void game_state::update_tilemap(const float &dt)
{
    map->update();
    map->update_collision(plr, dt);
}

void game_state::update(const float &dt)
{
    update_input(dt);
    if (!paused)
    {
        update_view(dt);
        update_player_input(dt);
        update_tilemap(dt);
        plr->update(dt);
        update_player_gui(dt);
    }
    else if (paused)
    {
        p_menu->update(mouse_pos_window);
        update_menu_buttons();
    }
}
void game_state::render(sf::RenderTarget *target)
{
    if (!target)
        target = window;

    render_texture.clear();

    render_texture.setView(view);

    map->render(render_texture,
                plr->get_gridpos(static_cast<int>(state_details->grid_size)),
                &core_shader,
                plr->get_center(),
                false);
    plr->render(render_texture, &core_shader);

    map->render_deferred(render_texture, &core_shader, plr->get_center());

    render_texture.setView(render_texture.getDefaultView());
    plr_gui->render(render_texture);

    if (paused)
        p_menu->render(render_texture);

    // Final render
    render_texture.display();
    target->draw(render_sprite);
}

game_state::~game_state()
{
    delete map;
    delete p_menu;
    delete plr;
    delete plr_gui;
}