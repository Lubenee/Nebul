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

const sf::Vector2u entity::get_gridpos(const size_t grid_sizeu) const
{
    if (hc)
        return sf::Vector2u(static_cast<size_t>(hc->get_pos().x) / grid_sizeu,
                            static_cast<size_t>(hc->get_pos().y) / grid_sizeu);
    return sf::Vector2u(static_cast<size_t>(sprite.getPosition().x) / grid_sizeu,
                        static_cast<size_t>(sprite.getPosition().y) / grid_sizeu);
}

const sf::FloatRect entity::get_next_pos(const float &dt) const
{
    if (hc && mc)
        return hc->get_next_pos(mc->get_velocity() * dt);

    return sf::FloatRect();
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
}