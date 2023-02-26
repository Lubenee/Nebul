#ifndef ATTRIBUTE_COMPONENT_H
#define ATTRIBUTE_COMPONENT_H

#include "Constants.hpp"

struct attribute_component
{
public:
    attribute_component(int _level);
    ~attribute_component() = default;

    /*  Leveling.   */
    size_t level;
    size_t exp;
    size_t exp_next;
    size_t attribute_points;

    /*  Attributes.  */
    int strength;
    int defence;
    int vitality;
    int dexterity;
    int agility;
    int endurance;
    int intelligence;

    /*  Stats.   */
    float hp;
    int hp_max;

    float stamina;
    int stamina_max;

    int damage;
    int damage_min;
    int damage_max;

    /*  Functions.   */
    void update();
    void update_level();
    void update_stats(const bool reset);
    void print() const;

    void lose_hp(const int _hp);
    void lose_exp(const unsigned _exp);

    void gain_hp(const int _hp);
    void gain_exp(const int _exp);

    bool regenerated_stamina;

private:
    sf::Clock stamina_reg_time;
};

#endif