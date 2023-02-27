#include "../Headers/pch.h"

#include "../Headers/MovmentComponent.hpp"

movment_component::movment_component(sf::Sprite &sprite, const float _max_velocity, float _acc, float _dec)
    : sprite(sprite), max_velocity(_max_velocity), acceleration(_acc), deceleration(_dec), max_velocity_copy(_max_velocity)
{
    this->velocity.x = 0;
    this->velocity.y = 0;
}

void movment_component::update(const float &dt)
{
    // Check for positive x
    if (velocity.x > 0.f)
    {
        // Max velocity check
        if (velocity.x > max_velocity)
            velocity.x = max_velocity;

        // Deceleration x positive
        velocity.x -= deceleration;
        if (velocity.x < 0.f)
            velocity.x = 0.f;
    }
    // Check for negative x
    else if (velocity.x < 0.f)
    {
        // Max velocity check
        if (velocity.x < -max_velocity)
            velocity.x = -max_velocity;

        // Deceleration x negative
        velocity.x += deceleration;
        if (velocity.x > 0.f)
            velocity.x = 0.f;
    }
    // Check for positive y
    if (velocity.y > 0.f)
    {
        if (velocity.y > max_velocity)
            velocity.y = max_velocity;

        velocity.y -= deceleration;
        if (velocity.y < 0.f)
            velocity.y = 0.f;
    }
    // Check for negative y
    else if (velocity.y < 0.f)
    {
        // Max velocity check
        if (velocity.y < -max_velocity)
            velocity.y = -max_velocity;

        // Deceleration y negative
        velocity.y += deceleration;
        if (velocity.y > 0.f)
            velocity.y = 0.f;
    }

    sprite.move(velocity * dt);
}

void movment_component::move(const float dir_x, const float dir_y, const float &dt, const float run_value)
{
    // Accelerating a sprite until it reaches max velocity
    velocity.x += acceleration * dir_x * run_value;
    velocity.y += acceleration * dir_y * run_value;

    if (run_value != 1)
        max_velocity = max_velocity_copy + run_value * 50;
    else
        max_velocity = max_velocity_copy;
}

void movment_component::reset_velocity()
{
    velocity *= 0.f;
}

void movment_component::reset_velocityX()
{
    velocity.x = 0.f;
}

void movment_component::reset_velocityY()
{
    velocity.y = 0.f;
}

sf::Vector2f &movment_component::get_velocity()
{
    return velocity;
}

const float &movment_component::get_max_velocity() const
{
    return max_velocity;
}

const bool movment_component::get_state(const short unsigned state) const
{
    switch (state)
    {
    case IDLE:
        return ((velocity.x == 0.f && velocity.y == 0.f) ? true : false);
        break;
    case MOVING:
        return ((velocity.x != 0.f || velocity.y != 0.f) ? true : false);
        break;
    case LEFT:
        return (velocity.x < 0.f ? true : false);
        break;
    case RIGHT:
        return (velocity.x > 0.f ? true : false);
        break;
    case UP:
        return (velocity.y < 0.f ? true : false);
        break;
    case DOWN:
        return (velocity.y > 0.f ? true : false);
        break;
    default:
        break;
    }

    return false;
}

movment_component::~movment_component()
{
}