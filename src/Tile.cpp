#include "../Headers/pch.h"
#include "../Headers/Tile.hpp"

tile::tile(float x, float y, float grid_size, sf::Texture &_tex, const sf::IntRect &_rect)
{
    shape.setSize(sf::Vector2f(grid_size, grid_size));
    shape.setPosition(x, y);
    shape.setTexture(&_tex);
    shape.setTextureRect(_rect);

    // shape.setFillColor(sf::Color::Green);
    // shape.setOutlineThickness(-1.f);
    // shape.setOutlineColor(sf::Color::Black);
}

void tile::update() {}

void tile::render(sf::RenderTarget &target)
{
    target.draw(shape);
}

tile::~tile() {}