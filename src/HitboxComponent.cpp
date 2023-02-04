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
    hitbox.setOutlineThickness(1.f);
    hitbox.setOutlineColor(sf::Color::Magenta);

    offset.x = offset_x;
    offset.y = offset_y;
}

void hitbox_component::update()
{
    hitbox.setPosition(sprite.getPosition().x + offset.x, sprite.getPosition().y + offset.y);
}

bool hitbox_component::intersects(const sf::FloatRect &rect)
{
    return hitbox.getGlobalBounds().intersects(rect);
}

void hitbox_component::render(sf::RenderTarget &target)
{
    target.draw(hitbox);
}

hitbox_component::~hitbox_component() {}