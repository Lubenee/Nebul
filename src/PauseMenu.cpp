#include "../Headers/pch.h"

#include "../Headers/PauseMenu.hpp"

pause_menu::pause_menu(sf::RenderWindow &window, sf::Font &_font)
    : font(_font)
{
    // Background cosmetics
    background.setSize(sf::Vector2f(
        static_cast<float>(window.getSize().x),
        static_cast<float>(window.getSize().y)));
    background.setFillColor(sf::Color(20, 20, 20, 100));
    background.setPosition(0.f, 0.f);

    // Container cosmetics
    container.setSize(sf::Vector2f(
        static_cast<float>(window.getSize().x) / 4.f,
        static_cast<float>(window.getSize().y) - 60.f));
    container.setFillColor(sf::Color(255, 155, 55, 155));
    container.setPosition(window.getSize().x / 2.f - container.getSize().x / 2.f, 30.f);

    // Text cosmetics
    text.setFont(font);
    text.setFillColor(sf::Color(255, 255, 255, 200));
    text.setCharacterSize(25);
    text.setString("PAUSED");
    text.setPosition(sf::Vector2f(
        container.getPosition().x + container.getSize().x / 2.f - text.getGlobalBounds().width / 2.f,
        container.getPosition().y + 40.f));

    init_buttons();
}

void pause_menu::init_buttons()
{
    float width = 250.f;
    float height = 50.f;
    float x = container.getPosition().x + container.getSize().x / 2.f - width / 2.f;
    buttons["QUIT"] = new GUI::button(x, 500.f, width, height,
                                      "Quit", &font, 30,
                                      sf::Color(150, 150, 150, 200),
                                      sf::Color(250, 250, 250, 250),
                                      sf::Color(40, 40, 40, 80),
                                      sf::Color(70, 70, 70, 0),
                                      sf::Color(150, 150, 150, 0),
                                      sf::Color(20, 20, 20, 0));
}

void pause_menu::update(const sf::Vector2i &mouse_pos)
{
    for (auto &i : buttons)
        i.second->update(mouse_pos);
}

void pause_menu::render(sf::RenderTarget &target)
{
    target.draw(background);
    target.draw(container);
    target.draw(text);

    for (auto &i : buttons)
        i.second->render(target);
}

void pause_menu::add_button(const std::string &key, float y, const std::string &text)
{
    float width = 200.f;
    float height = 65.f;
    float x = container.getPosition().x + container.getSize().x / 2.f - width / 2.f;
    buttons[key] = new GUI::button(x, y, width, height,
                                   text, &font, 30,
                                   sf::Color(150, 150, 150, 200),
                                   sf::Color(250, 250, 250, 250),
                                   sf::Color(40, 40, 40, 80),
                                   sf::Color(70, 70, 70, 0),
                                   sf::Color(150, 150, 150, 0),
                                   sf::Color(20, 20, 20, 0));
}

std::map<std::string, GUI::button *> &pause_menu::get_buttons()
{
    return buttons;
}

const bool pause_menu::is_button_pressed(const std::string key) const
{
    return buttons.at(key)->pressed();
}

pause_menu::~pause_menu()
{
    for (auto &i : buttons)
        delete i.second;
}