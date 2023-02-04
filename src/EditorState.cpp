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
}

void editor_state::init_gui()
{
    selector.setFillColor(sf::Color::Transparent);
    selector.setSize(sf::Vector2f(state_details->grid_size, state_details->grid_size));
    selector.setOutlineThickness(-1.f);
    selector.setOutlineColor(sf::Color(50, 200, 20, 255));
}

void editor_state::init_pause_menu()
{
    p_menu = new pause_menu(*window, font);
}

void editor_state::init_tilemap()
{
    map = new tilemap(state_details->grid_size, 10, 10);
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
    // buttons["GAME_STATE"] = new button(320.f, 140.f, 197.f, 40.f,
    //                                    "New Game", &font, 30,
    //                                    sf::Color(150, 150, 150, 200),
    //                                    sf::Color(250, 250, 250, 250),
    //                                    sf::Color(40, 40, 40, 80),
    //                                    sf::Color(70, 70, 70, 100),
    //                                    sf::Color(150, 150, 150, 100),
    //                                    sf::Color(20, 20, 20, 100));
}

void editor_state::update_buttons()
{
    for (auto &i : buttons)
        i.second->update(mouse_pos_view);
}

void editor_state::update_gui()
{
    selector.setPosition(mouse_pos_view);
}

void editor_state::update_input(const float &dt)
{
    update_mouse_pos();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds["CLOSE"])) && pressable_button())
        paused = (paused == true ? false : true);
}

void editor_state::update_pause_menu()
{
    p_menu->update(mouse_pos_view);
}

void editor_state::button_handler()
{
    if (p_menu->is_button_pressed("QUIT") && pt.pressable_button())
        end_state();
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

        update_buttons();
        update_gui();
    }
}

void editor_state::render_buttons(sf::RenderTarget &target)
{
    for (auto &i : buttons)
        i.second->render(target);
}

void editor_state::render_gui(sf::RenderTarget &target)
{
    target.draw(selector);
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
}
