#include "../Headers/pch.h"
#include "../Headers/HitboxComponent.hpp"

hitbox_component::hitbox_component(float offset_x, float offset_y, float width, float height, sf::Sprite &sprite)
    : sprite(sprite)
{
    hitbox.setPosition(
        sprite.getPosition().x + offset_x,
        sprite.getPosition().y + offset_y);
    hitbox.setSize(sf::Vector2f(width, height));

    hitbox.setFillColor(sf::Color::Transparent);
    hitbox.setOutlineThickness(-1.f);
    hitbox.setOutlineColor(sf::Color::Magenta);

    offset.x = offset_x;
    offset.y = offset_y;

    next_pos.left = 0.f;
    next_pos.top = 0.f;
    next_pos.width = width;
    next_pos.height = height;
}

void hitbox_component::update()
{
    hitbox.setPosition(sprite.getPosition().x + offset.x, sprite.getPosition().y + offset.y);
}

void hitbox_component::render(sf::RenderTarget &target)
{
    target.draw(hitbox);
}

bool hitbox_component::intersects(const sf::FloatRect &rect)
{
    return hitbox.getGlobalBounds().intersects(rect);
}

void hitbox_component::set_pos(const float _x, const float _y)
{
    hitbox.setPosition(_x, _y);
    sprite.setPosition(_x - offset.x, _y - offset.y);
}

void hitbox_component::set_pos(const sf::Vector2f &_pos)
{
    hitbox.setPosition(_pos);
    sprite.setPosition(_pos.x - offset.x, _pos.y - offset.y);
}

const sf::FloatRect hitbox_component::get_global_bounds() const
{
    return hitbox.getGlobalBounds();
}

const sf::Vector2f &hitbox_component::get_pos() const
{
    return hitbox.getPosition();
}

const sf::FloatRect hitbox_component::get_next_pos(const sf::Vector2f &_vel)
{
    next_pos.left = hitbox.getPosition().x + _vel.x;
    next_pos.top = hitbox.getPosition().y + _vel.y;
    return next_pos;
}

hitbox_component::~hitbox_component() {}