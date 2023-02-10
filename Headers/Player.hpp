#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.hpp"
class entity;

class player : public entity
{
public:
    player(float _x, float _y, sf::Texture &_tex_sheet);
    virtual void update(const float &dt) override;
    void update_animation(const float &dt);
    void update_attack();

    void lose_hp(const int hp);
    void lose_exp(const unsigned exp);

    void gain_hp(const int hp);
    void gain_exp(const unsigned exp);

    attribute_component *get_attribute_component();

    virtual ~player();

private:
    bool attacking;
    void init_variables();
};

#endif