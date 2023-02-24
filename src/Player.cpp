#include "../Headers/pch.h"
#include "../Headers/Player.hpp"

player::player(float _x, float _y, sf::Texture &_tex_sheet)
{
    init_variables();

    set_pos(_x, _y);

    create_hitbox_component(10.f, 5.f, 44.f, 54.f, sprite);
    create_movment_component(250.f, 1500.f, 900.f);
    create_animation_component(_tex_sheet);
    create_attribute_component(1);

    ac->add_animation("IDLE", 15.f, 0, 0, 8, 0, 64, 64);
    ac->add_animation("WALK_DOWN", 10.f, 0, 1, 3, 1, 64, 64);
    ac->add_animation("WALK_LEFT", 10.f, 4, 1, 7, 1, 64, 64);

    ac->add_animation("WALK_RIGHT", 10.f, 8, 1, 11, 1, 64, 64);
    ac->add_animation("WALK_UP", 10.f, 12, 1, 15, 1, 64, 64);

    // ac->add_animation("ATTACK", 4.f, 0, 2, 13, 2, 192 * 2, 192);
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
        ac->play("WALK_LEFT", dt, mc->get_velocity().x, mc->get_max_velocity());
    }
    else if (mc->get_state(RIGHT))
    {
        ac->play("WALK_RIGHT", dt, mc->get_velocity().x, mc->get_max_velocity());
    }
    else if (mc->get_state(UP))
    {
        ac->play("WALK_UP", dt, mc->get_velocity().y, mc->get_max_velocity());
    }
    else if (mc->get_state(DOWN))
    {
        ac->play("WALK_DOWN", dt, mc->get_velocity().y, mc->get_max_velocity());
    }
}

void player::update_attack()
{
    // if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    //     attacking = true;
}

void player::update(const float &dt)
{
    // TODO Debug print
    // at_c->print();

    mc->update(dt);
    hc->update();
    update_attack();
    update_animation(dt);
}

void player::lose_hp(const int hp)
{
    at_c->hp -= hp;
    if (at_c->hp < 0)
        at_c->hp = 0;
}
void player::lose_exp(const unsigned exp)
{
    at_c->exp -= exp;
    if (at_c->exp < 0)
        at_c->exp = 0;
}

void player::gain_hp(const int hp)
{
    at_c->hp += hp;
    if (at_c->hp > at_c->hp_max)
        at_c->hp = at_c->hp_max;
}
void player::gain_exp(const unsigned exp)
{
    at_c->gain_exp(exp);
}

attribute_component *player::get_attribute_component()
{
    return this->at_c;
}

player::~player()
{
}