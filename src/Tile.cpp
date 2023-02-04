#include "../Headers/pch.h"
#include "../Headers/Tile.hpp"

tile::tile(float x, float y, float grid_size)
{
    shape.setSize(sf::Vector2f(grid_size, grid_size));
    shape.setFillColor(sf::Color::Magenta);
    shape.setPosition(x, y);
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(-1.f);
}

void tile::update() {}

void tile::render(sf::RenderTarget &target)
{
    target.draw(shape);
}

tile::~tile() {}