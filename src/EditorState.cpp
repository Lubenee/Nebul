#include "../Headers/pch.h"
#include "../Headers/EditorState.hpp"

editor_state::editor_state(state_data *_state_data)
    : state(_state_data)
{
    init_keybinds();
    init_fonts();
    init_buttons();
    init_background();
    init_tilemap();
    init_pause_menu();
    init_gui();
    init_text();
}

void editor_state::init_gui()
{
    sidebar.setSize(sf::Vector2f(80.f, static_cast<float>(state_details->gfx_settings->resolution.height)));
    sidebar.setFillColor(sf::Color(50, 50, 50, 100));
    sidebar.setOutlineColor(sf::Color(200, 200, 200, 150));
    sidebar.setOutlineThickness(-1.f);

    selector.setFillColor(sf::Color(200, 200, 200, 125));
    selector.setSize(sf::Vector2f(state_details->grid_size, state_details->grid_size));
    selector.setOutlineThickness(-1.f);
    selector.setOutlineColor(sf::Color(50, 200, 20, 255));
    selector.setTexture(map->get_tilesheet());

    tex_selector = new GUI::texture_selector(20.f, 20.f, 800.f, 200.f, state_details->grid_size, *(map->get_tilesheet()), font);
}

void editor_state::init_text()
{
    mouse_text.setFont(font);
    mouse_text.setCharacterSize(10);
    mouse_text.setFillColor(sf::Color::White);
}

void editor_state::init_pause_menu()
{
    p_menu = new pause_menu(*window, font);
    p_menu->add_button("SAVE", 190.f, "Save");
    p_menu->add_button("LOAD", 260.f, "Load");
}

void editor_state::init_tilemap()
{
    map = new tilemap(state_details->grid_size, 35, 35, "../Assets/tiles/tilesheet1.png");
    texture_rect = sf::IntRect(200, 0, static_cast<int>(state_details->grid_size), static_cast<int>(state_details->grid_size));
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

void editor_state::init_background()
{
}

void editor_state::init_buttons()
{
}

void editor_state::update_buttons()
{
    for (auto &i : buttons)
        i.second->update(mouse_pos_view);

    std::stringstream ss;
    ss << mouse_pos_view.x << ' ' << mouse_pos_view.y << '\n'
       << mouse_pos_grid.x << ' ' << mouse_pos_grid.y << '\n'
       << texture_rect.left << ' ' << texture_rect.top;
    mouse_text.setString(ss.str());
}

void editor_state::update_gui()
{

    tex_selector->update(mouse_pos_window);
    if (!tex_selector->get_active())
    {
        // for snappy selection
        selector.setPosition(mouse_pos_grid.x * state_details->grid_size, mouse_pos_grid.y * state_details->grid_size);
        selector.setTextureRect(texture_rect);
    }

    mouse_text.setPosition(mouse_pos_view.x - mouse_text_offset, mouse_pos_view.y);
    std::stringstream ss;
    ss << mouse_pos_view.x << ' ' << mouse_pos_view.y << '\n'
       << mouse_pos_grid.x << ' ' << mouse_pos_grid.y << '\n'
       << texture_rect.left << ' ' << texture_rect.top;
    mouse_text.setString(ss.str());
}

void editor_state::update_input(const float &dt)
{
    update_mouse_pos();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds["CLOSE"])) && pressable_button())
        paused = (paused == true ? false : true);
}

void editor_state::update_editor_input()
{
    // Add a new tile
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (!sidebar.getGlobalBounds().contains(sf::Vector2f(mouse_pos_view)))
        {
            if (!tex_selector->get_active())
                map->add_tile(mouse_pos_grid.x, mouse_pos_grid.y, 0, texture_rect);
            else
                texture_rect = tex_selector->get_texture_rect();
        }
    }
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        if (!sidebar.getGlobalBounds().contains(sf::Vector2f(mouse_pos_view)))

            if (!tex_selector->get_active())
                map->remove_tile(mouse_pos_grid.x, mouse_pos_grid.y, 0);
    }
}

void editor_state::update_pause_menu()
{
    p_menu->update(mouse_pos_view);
}

void editor_state::button_handler()
{
    if (p_menu->is_button_pressed("QUIT") && pt.pressable_button())
        end_state();
    else if (p_menu->is_button_pressed("SAVE") && pt.pressable_button())
        map->save_tilemap("savefile.sav");
    else if (p_menu->is_button_pressed("LOAD") && pt.pressable_button())
        map->load_tilemap("savefile.sav");
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
    {
        tex_selector->update(mouse_pos_window);
        update_buttons();
        update_gui();
        update_editor_input();
    }
}

void editor_state::render_buttons(sf::RenderTarget &target)
{
    for (auto &i : buttons)
        i.second->render(target);
}

void editor_state::render_gui(sf::RenderTarget &target)
{
    if (!tex_selector->get_active())
        target.draw(selector);

    tex_selector->render(target);
    target.draw(mouse_text);

    target.draw(sidebar);
}

void editor_state::render(sf::RenderTarget *target)
{
    if (!target)
        target = window;

    render_buttons(*target);
    map->render(*target);
    render_gui(*target);

    if (paused)
        p_menu->render(*target);
}

editor_state::~editor_state()
{
    for (auto &i : buttons)
        delete i.second;

    delete p_menu;
    delete map;
    delete tex_selector;
}
