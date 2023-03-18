#include "../Headers/pch.h"
#include "../Headers/EditorState.hpp"

editor_state::editor_state(state_data *_state_data)
    : state(_state_data), cam_speed(700.f)
{
    init_keybinds();
    init_tilemap();
    init_fonts();
    init_pause_menu();
    init_view();

    init_editor_data();

    init_modes();
}

void editor_state::init_editor_data()
{
    editor_details.view = &this->view;
    editor_details.font = &this->font;
    editor_details.keybinds = &this->keybinds;
    editor_details.mouse_pos_grid = &this->mouse_pos_grid;
    editor_details.mouse_pos_screen = &this->mouse_pos_screen;
    editor_details.mouse_pos_view = &this->mouse_pos_view;
    editor_details.mouse_pos_window = &this->mouse_pos_window;
    editor_details.map_size = &this->map_size;
}

void editor_state::init_modes()
{
    modes.push_back(new default_mode(state_details, map, &editor_details));
}

void editor_state::init_view()
{
    view.setSize(state_details->gfx_settings->resolution.width, state_details->gfx_settings->resolution.height);
    view.setCenter(
        state_details->gfx_settings->resolution.width / 2.f,
        state_details->gfx_settings->resolution.height / 2.f);
}

void editor_state::init_pause_menu()
{
    const sf::VideoMode &vm = state_details->gfx_settings->resolution;
    p_menu = new pause_menu(state_details->gfx_settings->resolution, font);

    p_menu->add_button("SAVE", GUI::p2p_y(20, vm), GUI::p2p_x(15.f, vm), GUI::p2p_y(6.4f, vm), GUI::calc_char_size(vm), "Save");
    p_menu->add_button("LOAD", GUI::p2p_y(30, vm), GUI::p2p_x(15.f, vm), GUI::p2p_y(6.4f, vm), GUI::calc_char_size(vm), "Load");
    p_menu->add_button("QUIT", GUI::p2p_y(85, vm), GUI::p2p_x(15.f, vm), GUI::p2p_y(6.4f, vm), GUI::calc_char_size(vm), "Quit");
}

void editor_state::init_tilemap()
{
    map = new tilemap("savefile.sav");
    map_size = map->get_map_size_pixels();
}

void editor_state::init_keybinds()
{
    std::ifstream ifs;
    ifs.open("../Config/editorState_keybinds.ini", std::ios::in);
    if (ifs.is_open())
    {
        std::string key = "";
        std::string key_value = "";
        while (ifs >> key >> key_value)
            keybinds[key] = supported_keys->at(key_value);
    }
    ifs.close();
}

void editor_state::init_fonts()
{
    if (!font.loadFromFile("../Fonts/pixelfont.TTF"))
        throw("ERROR::EDITOR_STATE_H::COULD NOT LOAD FONT");
}

void editor_state::update_input(const float &dt)
{
    update_mouse_pos(&view);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds["PAUSE"])) && pressable_button())
        paused == false ? set_pause(true) : set_pause(false);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds["MOVE_CAM_RIGHT"])))
        view.move((cam_speed * dt), 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds["MOVE_CAM_LEFT"])))
        view.move(-(cam_speed * dt), 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds["MOVE_CAM_UP"])))
        view.move(0, -(cam_speed * dt));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds["MOVE_CAM_DOWN"])))
        view.move(0, (cam_speed * dt));
}

void editor_state::update_pause_menu()
{
    p_menu->update(mouse_pos_window);
}

void editor_state::button_handler()
{
    if (p_menu->is_button_pressed("QUIT") && pressable_button())
        end_state();
    else if (p_menu->is_button_pressed("SAVE") && pressable_button())
        map->save_tilemap("savefile.sav");
    else if (p_menu->is_button_pressed("LOAD") && pressable_button())
        map->load_tilemap("savefile.sav");
}

void editor_state::update_modes(const float &dt)
{
    modes[em::DEFAULT_MODE]->update(dt);
}

void editor_state::update(const float &dt)
{
    update_input(dt);
    if (paused)
    {
        button_handler();
        update_pause_menu();
    }
    else
        update_modes(dt);
}

void editor_state::render_modes(sf::RenderTarget &target)
{
    modes[em::DEFAULT_MODE]->render(&target);
}

void editor_state::render(sf::RenderTarget *target)
{

    if (!target)
        target = window;

    target->setView(view);
    map->render(*target, mouse_pos_grid, nullptr, sf::Vector2f(), true);
    map->render_deferred(*target);

    target->setView(window->getDefaultView());

    render_modes(*target);

    if (paused)
    {
        target->setView(window->getDefaultView());
        p_menu->render(*target);
    }
}

editor_state::~editor_state()
{
    delete p_menu;
    delete map;

    for (auto &i : modes)
        delete i;
    modes.clear();
}
