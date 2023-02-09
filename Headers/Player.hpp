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

    virtual ~player();

private:
    bool attacking;
    void init_variables();
};

#endif