#include "../Headers/pch.h"
#include "../Headers/Entity.hpp"

entity::entity()
{
    mc = nullptr;
    ac = nullptr;
    hc = nullptr;
    texture = nullptr;
}

void entity::set_texture(sf::Texture &_texture)
{
    texture = &_texture;
    sprite.setTexture(*texture);
}

void entity::create_movment_component(const float max_velocity, const float _acceleration, const float _deceleration)
{
    mc = new movment_component(sprite, max_velocity, _acceleration, _deceleration);
}

void entity::create_animation_component(sf::Texture &texture_sheet)
{
    ac = new animation_component(this->sprite, texture_sheet);
}

void entity::create_hitbox_component(float offset_x, float offset_y, float width, float height, sf::Sprite &_sprite)
{
    hc = new hitbox_component(offset_x, offset_y, width, height, _sprite);
}

void entity::move(const float _x, const float _y, const float &dt)
{
    if (mc)
        mc->move(_x, _y, dt);
    else
        sprite.move(_x, _y);
}

void entity::update(const float &dt)
{
    if (mc)
        mc->update(dt);
}

void entity::render(sf::RenderTarget &target)
{
    target.draw(sprite);
    if (hc)
        hc->render(target);
}

const sf::Vector2f &entity::get_pos() const
{
    if (hc)
        return hc->get_pos();

    return sprite.getPosition();
}

const sf::FloatRect entity::get_global_bounds() const
{
    if (hc)
        return hc->get_global_bounds();
    return sprite.getGlobalBounds();
}

void entity::set_pos(const float _x, const float _y)
{
    if (hc)
        hc->set_pos(_x, _y);
    else
        sprite.setPosition(_x, _y);
}

entity::~entity()
{
    delete mc;
    delete ac;
    delete hc;
}