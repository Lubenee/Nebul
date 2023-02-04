#include "../Headers/pch.h"

#include "../Headers/MainMenuState.hpp"

main_menu_state::main_menu_state(state_data *state_data)
    : state(state_data)
{
    init_keybinds();
    init_fonts();
    init_buttons();
    init_background();
}


void main_menu_state::init_keybinds()
{
    std::ifstream ifs;
    ifs.open("../Config/mainmenuState_keybinds.ini", std::ios::in);
    if (ifs.is_open())
    {
        std::string key = "";
        std::string key_value = "";
        while (ifs >> key >> key_value)
            keybinds[key] = state_details->supported_keys->at(key_value);
    }
    ifs.close();
}

void main_menu_state::init_fonts()
{
    if (!font.loadFromFile("../Fonts/pixelfont.TTF"))
        throw("ERROR::MAIN_MENU_STATE_H::COULD NOT LOAD FONT");
}

void main_menu_state::init_background()
{
    if (!background_texture.loadFromFile("../Assets/Images/Backgrounds/bckgr1.jpg"))
        throw("ERROR::MAIN_MENU_STATE::FAILED TO LOAD BACKGROUND TEXTURE.");
    background.setSize(sf::Vector2f(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)));

    background.setTexture(&background_texture);
}

void main_menu_state::init_buttons()
{
    buttons["GAME_STATE"] = new GUI::button(320.f, 140.f, 197.f, 40.f,
                                            "New Game", &font, 30,
                                            sf::Color(150, 150, 150, 200),
                                            sf::Color(250, 250, 250, 250),
                                            sf::Color(40, 40, 40, 80),
                                            sf::Color(70, 70, 70, 0),
                                            sf::Color(150, 150, 150, 0),
                                            sf::Color(20, 20, 20, 0));

    buttons["EDITOR_STATE"] = new GUI::button(320.f, 225.f, 200.f, 45.f,
                                              "Editor", &font, 30,
                                              sf::Color(150, 150, 150, 200),
                                              sf::Color(250, 250, 250, 250),
                                              sf::Color(40, 40, 40, 80),
                                              sf::Color(70, 70, 70, 0),
                                              sf::Color(150, 150, 150, 0),
                                              sf::Color(20, 20, 20, 0));

    buttons["SETTINGS_STATE"] = new GUI::button(320.f, 300.f, 200.f, 45.f,
                                                "Settings", &font, 30,
                                                sf::Color(150, 150, 150, 200),
                                                sf::Color(250, 250, 250, 250),
                                                sf::Color(40, 40, 40, 80),
                                                sf::Color(70, 70, 70, 0),
                                                sf::Color(150, 150, 150, 0),
                                                sf::Color(20, 20, 20, 0));

    buttons["EXIT_STATE"] = new GUI::button(320.f, 420.f, 200.f, 45.f,
                                            "Quit", &font, 30,
                                            sf::Color(150, 150, 150, 200),
                                            sf::Color(250, 250, 250, 250),
                                            sf::Color(40, 40, 40, 80),
                                            sf::Color(70, 70, 70, 0),
                                            sf::Color(150, 150, 150, 0),
                                            sf::Color(20, 20, 20, 0));
}

void main_menu_state::update_buttons()
{
    for (auto &i : buttons)
        i.second->update(mouse_pos_view);
}
void main_menu_state::update_input(const float &dt)
{
    update_mouse_pos();
}
void main_menu_state::update(const float &dt)
{
    background.setSize(sf::Vector2f(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)));
    update_input(dt);
    update_buttons();
    button_handler();
}

void main_menu_state::button_handler()
{
    /* New game */
    if (buttons["GAME_STATE"]->pressed())
        states->push(new game_state(state_details));

    /* Init Editor */
    else if (buttons["EDITOR_STATE"]->pressed())
        states->push(new editor_state(state_details));

    /* Settings */
    else if (buttons["SETTINGS_STATE"]->pressed())
        states->push(new settings_state(state_details));

    /* Quit game */
    else if (buttons["EXIT_STATE"]->pressed())
        end_state();
}

void main_menu_state::render_buttons(sf::RenderTarget &target)
{
    for (auto &i : buttons)
        i.second->render(target);
}

void main_menu_state::render(sf::RenderTarget *target)
{
    if (!target)
        target = window;
    target->draw(background);
    render_buttons(*target);
}

main_menu_state::~main_menu_state()
{
    for (auto &i : buttons)
        delete i.second;
}
