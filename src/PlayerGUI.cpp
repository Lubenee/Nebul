#include "../Headers/pch.h"
#include "../Headers/PlayerGUI.hpp"

player_gui::player_gui(player *_player)
{
    plr = _player;
    init_font();
    init_hp_bar();
}

void player_gui::init_font()
{
    if (!font.loadFromFile("../Fonts/pixelfont.TTF"))
        throw("ERROR::PLAYER_GUI::COULDN'T LOAD FONT.");
}

void player_gui::init_hp_bar()
{
    float width = 250.f;
    float height = 40.f;
    float x = 20.f;
    float y = 20.f;

    hp_bar_max_size = width;

    hp_bar_back.setSize(sf::Vector2f(width, height));
    hp_bar_back.setFillColor(sf::Color(50, 50, 50, 200));
    hp_bar_back.setPosition(x, y);

    hp_bar_inner.setSize(sf::Vector2f(width, height));
    hp_bar_inner.setFillColor(sf::Color(250, 20, 20, 200));
    hp_bar_inner.setPosition(hp_bar_back.getPosition());

    hp_bar_text.setFont(font);
    hp_bar_text.setPosition(hp_bar_inner.getPosition().x + 10.f, hp_bar_inner.getPosition().y + 5.f);
}

void player_gui::update_hp_bar()
{
    float scale = static_cast<float>(plr->get_attribute_component()->hp) / static_cast<float>(plr->get_attribute_component()->hp_max);
    hp_bar_inner.setSize(sf::Vector2f(std::floor(hp_bar_max_size * scale), hp_bar_inner.getSize().y));

    hp_bar_string = std::to_string(plr->get_attribute_component()->hp) + " / " + std::to_string(plr->get_attribute_component()->hp_max);
    hp_bar_text.setString(hp_bar_string);
}

void player_gui::update(const float &dt)
{
    update_hp_bar();
}

void player_gui::render_hp_bar(sf::RenderTarget &target)
{
    target.draw(hp_bar_back);
    target.draw(hp_bar_inner);
    target.draw(hp_bar_text);
}

void player_gui::render(sf::RenderTarget &target)
{
    render_hp_bar(target);
}

player_gui::~player_gui() {}