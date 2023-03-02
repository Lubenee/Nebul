#include "../Headers/pch.h"
#include "../Headers/GUI.hpp"

using namespace GUI;

check_box::check_box(float x, float y,
                     float width, float height,
                     sf::Color inactive_color,
                     sf::Color hover_color,
                     sf::Color active_color)
    : inactive_color(inactive_color), hover_color(hover_color), active_color(active_color)
{
    shape.setPosition(x, y);
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(inactive_color);
    active = false;
}

void check_box::update(const sf::Vector2i &mouse_pos)
{
    button_state = bs::idle;
    if (shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse_pos)))
    {
        button_state = bs::hovered;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->is_pressable())
            active = active == true ? false : true;
    }

    if (active)
        shape.setFillColor(active_color);
    else
        shape.setFillColor(inactive_color);

    if (button_state == bs::hovered)
        shape.setFillColor(hover_color);
}

void check_box::render(sf::RenderTarget &target)
{
    target.draw(shape);
}

void check_box::set_active()
{
    active = true;
}

const bool check_box::get_active() const
{
    return active;
}

check_box::~check_box() {}