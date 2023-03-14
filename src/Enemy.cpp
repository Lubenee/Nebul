#include "../Headers/pch.h"
#include "../Headers/Enemy.hpp"

enemy::enemy(float _x, float _y, sf::Texture &_tex_sheet)
{
    set_pos(_x, _y);

    create_hitbox_component(12.f, 10.f, 44.f, 54.f, sprite);
    create_movment_component(200.f, 80.f, 14.f);

    create_animation_component(_tex_sheet);
    ac->add_animation("IDLE", 15.f, 0, 0, 8, 0, 64, 64);
    ac->add_animation("WALK_DOWN", 10.f, 0, 1, 3, 1, 64, 64);
    ac->add_animation("WALK_LEFT", 10.f, 4, 1, 7, 1, 64, 64);

    ac->add_animation("WALK_RIGHT", 10.f, 8, 1, 11, 1, 64, 64);
    ac->add_animation("WALK_UP", 10.f, 12, 1, 15, 1, 64, 64);
}

void enemy::update_animations(const float &dt)
{
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

void enemy::update(const float &dt, const sf::Vector2f &mouse_pos_view)
{
    mc->update(dt);
    hc->update();
    update_animations(dt);
}

void enemy::render(sf::RenderTarget &target, sf::Shader *shader)
{
    if (shader)
    {
        shader->setUniform("hasTexture", true);
        shader->setUniform("light", get_center());
        target.draw(sprite, shader);
    }
    else
    {
        target.draw(sprite);
    }
}

enemy::~enemy() {}