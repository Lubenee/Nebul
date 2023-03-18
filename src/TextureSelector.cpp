#include "../Headers/pch.h"
#include "../Headers/GUI.hpp"

using namespace GUI;

texture_selector::texture_selector(const float _x, const float _y,
                                   const float _width, const float _height,
                                   const float grid_size, const sf::Texture &texture_sheet,
                                   sf::Font &font)
{
    this->grid_size = grid_size;
    active = false;
    hidden = true;
    float offset = grid_size;

    bounds.setSize(sf::Vector2f(_width, _height));
    bounds.setPosition(_x + offset, _y);
    bounds.setFillColor(sf::Color(50, 50, 50, 70));
    bounds.setOutlineThickness(-1.f);
    bounds.setOutlineColor(sf::Color(255, 255, 255, 100));

    sheet.setTexture(texture_sheet);
    sheet.setPosition(_x + offset, _y);

    if (sheet.getGlobalBounds().width > bounds.getGlobalBounds().width)
        sheet.setTextureRect(sf::IntRect(0, 0, bounds.getGlobalBounds().width, sheet.getGlobalBounds().height));

    if (sheet.getGlobalBounds().height > bounds.getGlobalBounds().height)
        sheet.setTextureRect(sf::IntRect(0, 0, sheet.getGlobalBounds().width, bounds.getGlobalBounds().height));

    selector.setPosition(_x + offset, _y);
    selector.setSize(sf::Vector2f(grid_size, grid_size));
    selector.setFillColor(sf::Color::Transparent);
    selector.setOutlineThickness(-1.f);
    selector.setOutlineColor(sf::Color::Red);

    texture_rect.width = static_cast<int>(grid_size);
    texture_rect.height = static_cast<int>(grid_size);

    hide_button = new button(_x, _y, 50.f, 35.f, "X", &font, 26,
                             sf::Color(70, 70, 70, 150), sf::Color(255, 255, 255, 200), sf::Color(40, 40, 40, 80),
                             sf::Color(70, 70, 70, 100), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50));
}

void texture_selector::update(const sf::Vector2i &mouse_pos_window)
{
    hide_button->update(mouse_pos_window);

    if (hide_button->pressed())
        hidden = (hidden == true ? false : true);

    if (hidden)
    {
        active = false;
        return;
    }
    else
    {

        if (bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse_pos_window)))
            active = true;
        else
            active = false;

        if (active)
        {
            this->mouse_pos_grid.x = (mouse_pos_window.x - static_cast<int>(bounds.getPosition().x)) /
                                     static_cast<unsigned>(grid_size);
            this->mouse_pos_grid.y = (mouse_pos_window.y - static_cast<int>(bounds.getPosition().y)) /
                                     static_cast<unsigned>(grid_size);

            selector.setPosition(bounds.getPosition().x + this->mouse_pos_grid.x * this->grid_size,
                                 bounds.getPosition().y + this->mouse_pos_grid.y * this->grid_size);

            // Update the texture rectangle
            texture_rect.left = static_cast<int>(selector.getPosition().x - bounds.getPosition().x);
            texture_rect.top = static_cast<int>(selector.getPosition().y - bounds.getPosition().y);
        }
    }
}

void texture_selector::render(sf::RenderTarget &target)
{
    if (!hidden)
    {
        target.draw(bounds);
        target.draw(sheet);
        if (active)
            target.draw(selector);
    }
    hide_button->render(target);
}

const bool texture_selector::get_active() const
{
    return active;
}

const bool texture_selector::get_hidden() const
{
    return hidden;
}

void texture_selector::set_hidden(bool _state)
{
    hidden = _state;
}

const sf::IntRect &texture_selector::get_texture_rect() const
{
    return texture_rect;
}

texture_selector::~texture_selector()
{
    delete hide_button;
}