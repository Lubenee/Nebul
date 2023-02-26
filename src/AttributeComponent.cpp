#include "../Headers/pch.h"
#include "../Headers/AttributeComponent.hpp"

attribute_component::attribute_component(int _level)
{
    level = _level;
    exp = 0;
    exp_next = static_cast<size_t>((50 / 3) * pow(level + 1, 2) - 2 * pow(level + 1, 2) + ((level + 1) * 10) - 12);
    attribute_points = 3;

    vitality = 5;
    strength = 5;
    dexterity = 5;
    agility = 5;
    intelligence = 5;
    endurance = 5;
    defence = 5;

    update_stats(true);
    update_level();
}

/*  Functions.  */
void attribute_component::update_stats(const bool reset)
{
    hp_max = vitality * 6 + vitality + strength / 2;
    stamina_max = endurance * 3 + 2 * strength + dexterity;
    damage_max = strength * 2 + strength / 2;
    damage_min = strength * 2 + strength / 4;

    if (reset)
    {
        hp = hp_max;
        stamina = stamina_max;
    }
}

void attribute_component::update()
{
    if (stamina < stamina_max && stamina_reg_time.getElapsedTime().asMilliseconds() >= GLOBAL_TICK_TIME_MILLISECONDS)
    {
        stamina += 0.2f;
        stamina_reg_time.restart();
    }
}

void attribute_component::update_level()
{
    while (exp >= exp_next)
    {
        exp -= exp_next;
        exp_next = static_cast<size_t>((50 / 3) * pow(level, 2) - 2 * pow(level, 2) + (level * 10) - 12);
        level++;
        attribute_points++;
    }
}

void attribute_component::lose_hp(const int _hp)
{
    hp -= _hp;
    if (hp < 0)
        hp = 0;
}
void attribute_component::lose_exp(const unsigned _exp)
{
    exp -= _exp;
    if (exp < 0)
        exp = 0;
}

void attribute_component::gain_hp(const int _hp)
{
    hp += _hp;
    if (hp > hp_max)
        hp = hp_max;
}

void attribute_component::gain_exp(const int _exp)
{
    exp += _exp;
    update_level();
}

void attribute_component::print() const
{
    std::cout << "Level: " << level << '\n'
              << "Exp: " << exp << '\n'
              << "Exp next: " << exp_next << '\n'
              << "Atribute points: " << attribute_points << '\n';
}