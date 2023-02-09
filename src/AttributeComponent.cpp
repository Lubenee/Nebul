#include "../Headers/pch.h"
#include "../Headers/AttributeComponent.hpp"

attribute_component::attribute_component(int _level)
{
    level = _level;
    exp = 0;
    exp_next = static_cast<size_t>((50 / 3) * pow(level, 3) - 6 * pow(level, 2) + (level * 17) - 12);
    attribute_points = 3;

    vitality = 1;
    strength = 1;
    dexterity = 1;
    agility = 1;
    intelligence = 1;

    update_stats(true);
    update_level();
}

/*  Functions.  */
void attribute_component::update_stats(const bool reset)
{
    hp_max = vitality * 6 + vitality + strength / 2;
    damage_max = strength * 2 + strength / 2;
    damage_min = strength * 2 + strength / 4;
    accuracy = dexterity * 4 + dexterity / 3 + intelligence / 4;
    defense = agility * 2 + agility / 2 + strength / 6;
    luck = intelligence * 2 + intelligence / 5;

    if (reset)
    {
        hp = hp_max;
    }
}

void attribute_component::update()
{
}

void attribute_component::update_level()
{
    while (exp >= exp_next)
    {
        exp -= exp_next;
        exp_next = static_cast<size_t>((50 / 3) * pow(level, 3) - 6 * pow(level, 2) + (level * 17) - 12);
        level++;
        attribute_points++;
    }
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