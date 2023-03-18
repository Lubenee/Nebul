#include "../Headers/pch.h"
#include "../Headers/EnemySpawner.hpp"

enemy_spawner::enemy_spawner(size_t x, size_t y, float grid_size, sf::Texture &_tex, const sf::IntRect &_rect,
                             int enemy_type, int amount, int time_to_spawn, float max_distance)
    : tile(x, y, grid_size, _tex, _rect), enemy_type(enemy_type), spawn_amount(amount), time_to_spawn(time_to_spawn), max_distance(max_distance)
{
    this->type = tt::SPAWNER;
    this->collision = false;
}

void enemy_spawner::update() {}

void enemy_spawner::render(sf::RenderTarget &target)
{
    // TODO clear this
    sf::RectangleShape temp;
    temp.setSize(sf::Vector2f(64, 64));
    temp.setFillColor(sf::Color::Magenta);

    target.draw(temp);
}

enemy_spawner::~enemy_spawner() {}