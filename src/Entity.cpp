#include "../Headers/pch.h"
#include "../Headers/Entity.hpp"

entity::entity()
{
    mc = nullptr;
    ac = nullptr;
    hc = nullptr;
    at_c = nullptr;
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

void entity::create_attribute_component(const int _level)
{
    at_c = new attribute_component(_level);
}

void entity::move(const float _x, const float _y, const float &dt, const float run_value)
{
    if (mc)
        mc->move(_x, _y, dt, run_value);
    else
        sprite.move(_x, _y);
}

void entity::update(const float &dt, const sf::Vector2f &mouse_pos_view)
{
    if (mc)
        mc->update(dt);
}

const sf::Vector2f &entity::get_pos() const
{
    if (hc)
        return hc->get_pos();

    return sprite.getPosition();
}

const sf::Vector2f entity::get_center() const
{
    if (hc)
        return hc->get_pos() +
               sf::Vector2f(
                   hc->get_global_bounds().width / 2.f,
                   hc->get_global_bounds().height / 2.f);

    return sprite.getPosition() +
           sf::Vector2f(
               sprite.getGlobalBounds().width / 2.f,
               sprite.getGlobalBounds().height / 2.f);
}

const sf::FloatRect entity::get_global_bounds() const
{
    if (hc)
        return hc->get_global_bounds();
    return sprite.getGlobalBounds();
}

const sf::Vector2i entity::get_gridpos(const int grid_size) const
{
    if (hc)
        return sf::Vector2i(static_cast<int>(hc->get_pos().x) / grid_size,
                            static_cast<int>(hc->get_pos().y) / grid_size);
    return sf::Vector2i(static_cast<int>(sprite.getPosition().x) / grid_size,
                        static_cast<int>(sprite.getPosition().y) / grid_size);
}

const sf::FloatRect entity::get_next_pos(const float &dt) const
{
    if (hc && mc)
        return hc->get_next_pos(mc->get_velocity() * dt);

    return sf::FloatRect(-1.f, -1.f, -1.f, -1.f);
}

void entity::reset_velocity()
{
    if (mc)
        mc->reset_velocity();
}

void entity::reset_velocityX()
{
    if (mc)
        mc->reset_velocityX();
}

void entity::reset_velocityY()
{
    if (mc)
        mc->reset_velocityY();
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
    delete at_c;
}