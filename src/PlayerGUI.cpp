#include "../Headers/pch.h"
#include "../Headers/PlayerGUI.hpp"

player_gui::player_gui(player *_player)
{
    plr = _player;
    init_font();
    init_hp_bar();
    init_exp_bar();
    init_level_bar();
}

void player_gui::init_font()
{
    if (!font.loadFromFile("../Fonts/pixelfont.TTF"))
        throw("ERROR::PLAYER_GUI::COULDN'T LOAD FONT.");
}

void player_gui::init_level_bar()
{
    float width = 30.f;
    float height = 30.f;
    float x = 20.f;
    float y = 130.f;

    level_bar_back.setSize(sf::Vector2f(width, height));
    level_bar_back.setFillColor(sf::Color(50, 50, 50, 200));
    level_bar_back.setPosition(x, y);

    level_bar_text.setFont(font);
    level_bar_text.setCharacterSize(12);
    level_bar_text.setPosition(level_bar_back.getPosition().x + 10.f, level_bar_back.getPosition().y + 5.f);
}

void player_gui::init_exp_bar()
{
    float width = 200.f;
    float height = 30.f;
    float x = 20.f;
    float y = 60.f;

    exp_bar_max_size = width;

    exp_bar_back.setSize(sf::Vector2f(width, height));
    exp_bar_back.setFillColor(sf::Color(50, 50, 50, 200));
    exp_bar_back.setPosition(x, y);

    exp_bar_inner.setSize(sf::Vector2f(width, height));
    exp_bar_inner.setFillColor(sf::Color(20, 20, 250, 200));
    exp_bar_inner.setPosition(exp_bar_back.getPosition());

    exp_bar_text.setFont(font);
    exp_bar_text.setCharacterSize(10);
    exp_bar_text.setPosition(exp_bar_inner.getPosition().x + 10.f, exp_bar_inner.getPosition().y + 8.f);
}

void player_gui::init_hp_bar()
{
    float width = 250.f;
    float height = 30.f;
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
    hp_bar_text.setCharacterSize(10);
    hp_bar_text.setPosition(hp_bar_inner.getPosition().x + 10.f, hp_bar_inner.getPosition().y + 8.f);
}

void player_gui::update_hp_bar()
{
    float scale = static_cast<float>(plr->get_attribute_component()->hp) / static_cast<float>(plr->get_attribute_component()->hp_max);
    hp_bar_inner.setSize(sf::Vector2f(std::floor(hp_bar_max_size * scale), hp_bar_inner.getSize().y));

    hp_bar_string = std::to_string(plr->get_attribute_component()->hp) + " / " + std::to_string(plr->get_attribute_component()->hp_max);
    hp_bar_text.setString(hp_bar_string);
}

void player_gui::update_exp_bar()
{
    float scale = static_cast<float>(plr->get_attribute_component()->exp) / static_cast<float>(plr->get_attribute_component()->exp_next);
    exp_bar_inner.setSize(sf::Vector2f(std::floor(exp_bar_max_size * scale), exp_bar_inner.getSize().y));
    exp_bar_string = std::to_string(plr->get_attribute_component()->exp) + " / " + std::to_string(plr->get_attribute_component()->exp_next);
    exp_bar_text.setString(exp_bar_string);
}

void player_gui::update_level_bar()
{
    level_bar_string = std::to_string(plr->get_attribute_component()->level);
    level_bar_text.setString(level_bar_string);
}

void player_gui::update(const float &dt)
{
    update_hp_bar();
    update_exp_bar();
    update_level_bar();
}

void player_gui::render_level_bar(sf::RenderTarget &target)
{
    target.draw(level_bar_back);
    target.draw(level_bar_text);
}

void player_gui::render_exp_bar(sf::RenderTarget &target)
{
    target.draw(exp_bar_back);
    target.draw(exp_bar_inner);
    target.draw(exp_bar_text);
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
    render_exp_bar(target);
    render_level_bar(target);
}

player_gui::~player_gui() {}