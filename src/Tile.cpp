#include "../Headers/pch.h"
#include "../Headers/Tile.hpp"

tile::tile()
{
    collision = false;
    type = -1;
}

tile::tile(size_t x, size_t y, float grid_size,
           sf::Texture &_tex, const sf::IntRect &_rect,
           bool collision, short type)
{
    shape.setSize(sf::Vector2f(grid_size, grid_size));
    shape.setPosition(x * grid_size, y * grid_size);
    shape.setTexture(&_tex);
    shape.setTextureRect(_rect);
    this->collision = collision;
    this->type = type;
}

void tile::update() {}

void tile::render(sf::RenderTarget &target)
{
    target.draw(shape);
}

const short tile::get_type() const
{
    return type;
}

const std::string tile::get_as_string() const
{
    std::stringstream ss;
    ss << shape.getTextureRect().left << ' '
       << shape.getTextureRect().top << ' '
       << collision << ' ' << type;
    return ss.str();
}

const sf::Vector2f &tile::get_pos() const
{
    return shape.getPosition();
}

const bool tile::get_collision() const
{
    return collision;
}

std::ostream &operator<<(std::ostream &os, const tile &tile)
{
    os << tile.shape.getTextureRect().left << ' '
       << tile.shape.getTextureRect().top << ' '
       << tile.collision << ' ' << tile.type;
    return os;
}

tile::~tile() {}