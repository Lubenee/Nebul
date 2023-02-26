#include "../Headers/pch.h"
#include "../Headers/Player.hpp"

player::player(float _x, float _y, sf::Texture &_tex_sheet)
{
    init_variables();

    set_pos(_x, _y);

    create_hitbox_component(12.f, 10.f, 44.f, 54.f, sprite);
    create_movment_component(250.f, 1600.f, 1000.f);
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
    weapon_texture.loadFromFile("../Assets/Images/Player/sword.png");
    weapon_sprite.setTexture(weapon_texture);
    weapon_sprite.setOrigin(
        weapon_sprite.getGlobalBounds().width / 2.f,
        weapon_sprite.getGlobalBounds().height);
    weapon_sprite.scale(1.5f, 1.5f);

    running = false;
    attacking = false;
    run_speed = 300.f;
}

void player::update_animation(const float &dt)
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

void player::update_attack()
{
    // if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    //     attacking = true;
}

void player::update_stamina()
{
    if (running && run_time.getElapsedTime().asMilliseconds() >= GLOBAL_TICK_TIME_MILLISECONDS)
    {
        at_c->stamina -= 0.7f;
        run_time.restart();
    }
}

void player::update(const float &dt, const sf::Vector2f &mouse_pos_view)
{
    // TODO Debug print
    // at_c->print();

    mc->update(dt);
    hc->update();
    update_attack();
    update_animation(dt);
    update_stamina();
    at_c->update();

    // Update visual weapon
    weapon_sprite.setPosition(get_center());
    float dx = mouse_pos_view.x - weapon_sprite.getPosition().x;
    float dy = mouse_pos_view.y - weapon_sprite.getPosition().y;

    const float Pi = 3.14159265;
    float deg = atan2(dy, dx) * 180 / Pi;

    weapon_sprite.setRotation(deg + 90.f);
}

void player::render(sf::RenderTarget &target, sf::Shader *shader)
{
    if (shader)
    {
        shader->setUniform("hasTexture", true);
        shader->setUniform("light", get_center());
        target.draw(sprite, shader);
        target.draw(weapon_sprite, shader);
    }
    else
    {
        target.draw(sprite);
        target.draw(weapon_sprite);
    }
}

void player::lose_hp(const int hp)
{
    at_c->lose_hp(hp);
}
void player::lose_exp(const unsigned exp)
{
    at_c->lose_exp(exp);
}

void player::gain_hp(const int hp)
{
    at_c->gain_hp(hp);
}
void player::gain_exp(const unsigned exp)
{
    at_c->gain_exp(exp);
}

void player::run(const bool state)
{
    running = state;
    if (running && at_c->stamina <= 0.3)
        running = false;
}

attribute_component *player::get_attribute_component()
{
    return this->at_c;
}

const bool player::get_running() const
{
    return running;
}

const float &player::get_run_speed() const
{
    return this->run_speed;
}

const bool player::get_regenerated_stamina() const
{
    return at_c->regenerated_stamina;
}

player::~player()
{
}