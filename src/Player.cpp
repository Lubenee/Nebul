#include "../Headers/pch.h"
#include "../Headers/Player.hpp"

player::player(float _x, float _y, sf::Texture &_tex_sheet)
{
    init_variables();

    set_pos(_x, _y);

    create_movment_component(400.f, 10.f, 3.f);
    create_hitbox_component(86.f, 67.f, 86.f, 100.f, sprite);
    create_animation_component(_tex_sheet);

    ac->add_animation("IDLE", 8.f, 0, 0, 13, 0, 192, 192);
    ac->add_animation("WALK", 3.f, 0, 1, 11, 1, 192, 192);
    ac->add_animation("ATTACK", 4.f, 0, 2, 13, 2, 192 * 2, 192);
}

void player::init_variables()
{
    attacking = false;
}

void player::update_animation(const float &dt)
{
    if (attacking)
    {
        // Set the origin point depending on direction
        if (sprite.getScale().x > 0.f)
        // Facing left
        {
            sprite.setOrigin(96.f, 0.f);
        }
        else
        // Facing right
        {
            sprite.setOrigin(258.f + 96.f, 0.f);
        }

        // Animate and check for animation end
        if (ac->play("ATTACK", dt, true))
        {
            attacking = false;

            if (sprite.getScale().x > 0.f)
            // Facing left
            {
                sprite.setOrigin(0.f, 0.f);
            }
            else
            // Facing right
            {
                sprite.setOrigin(258.f, 0.f);
            }
        }
    }

    if (mc->get_state(IDLE))
        ac->play("IDLE", dt);
    else if (mc->get_state(LEFT))
    {
        if (sprite.getScale().x < 0.f)
        {
            sprite.setOrigin(0.f, 0.f);
            sprite.setScale(1.f, 1.f);
        }
        ac->play("WALK", dt, mc->get_velocity().x, mc->get_max_velocity());
    }
    else if (mc->get_state(RIGHT))
    {
        if (sprite.getScale().x > 0.f)
        {
            sprite.setOrigin(258.f, 0.f);
            sprite.setScale(-1.f, 1.f);
        }
        ac->play("WALK", dt, mc->get_velocity().x, mc->get_max_velocity());
    }
    else if (mc->get_state(UP))
    {
        ac->play("WALK", dt, mc->get_velocity().y, mc->get_max_velocity());
    }
    else if (mc->get_state(DOWN))
    {
        ac->play("WALK", dt, mc->get_velocity().y, mc->get_max_velocity());
    }
}

void player::update_attack()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        attacking = true;
}

void player::update(const float &dt)
{
    mc->update(dt);
    hc->update();
    update_attack();
    update_animation(dt);
}

player::~player()
{
}