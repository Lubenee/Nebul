#ifndef ATTRIBUTE_COMPONENT_H
#define ATTRIBUTE_COMPONENT_H

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
    int vitality;
    int strength;
    int dexterity;
    int agility;
    int intelligence;

    /*  Stats.   */
    int hp;
    int hp_max;
    int damage;
    int damage_min;
    int damage_max;

    int accuracy;
    int defense;
    int luck;

    /*  Functions.   */
    void update_stats(const bool reset);
    void update();
    void update_level();
    void print() const;
    void gain_exp(const int _exp);
};

#endif