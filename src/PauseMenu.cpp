#include "../Headers/pch.h"

#include "../Headers/PauseMenu.hpp"

pause_menu::pause_menu(sf::VideoMode &vm, sf::Font &_font)
    : font(_font)
{
    // Background cosmetics
    background.setSize(sf::Vector2f(
        static_cast<float>(vm.width),
        static_cast<float>(vm.height)));
    background.setFillColor(sf::Color(20, 20, 20, 100));
    background.setPosition(0.f, 0.f);

    // Container cosmetics
    container.setSize(sf::Vector2f(
        static_cast<float>(vm.width) / 4.f,
        static_cast<float>(vm.height) - GUI::p2p_y(8.f, vm)));
    container.setFillColor(sf::Color(255, 155, 55, 155));
    container.setPosition(vm.width / 2.f - container.getSize().x / 2.f, 30.f);

    // Text cosmetics
    text.setFont(font);
    text.setFillColor(sf::Color(255, 255, 255, 200));
    text.setCharacterSize(GUI::calc_char_size(vm));
    text.setString("PAUSED");
    text.setPosition(sf::Vector2f(
        container.getPosition().x + container.getSize().x / 2.f - text.getGlobalBounds().width / 2.f,
        container.getPosition().y + GUI::p2p_y(4.f, vm)));
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

void pause_menu::add_button(
    const std::string &key,
    const float y,
    const float width,
    const float height,
    const unsigned char_size,
    const std::string &text)
{
    float x = container.getPosition().x + container.getSize().x / 2.f - width / 2.f;

    buttons[key] = new GUI::button(x, y, width, height,
                                   text, &font, char_size,
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