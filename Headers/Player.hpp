#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.hpp"
#include "Constants.hpp"

class entity;

class player : public entity
{
public:
    player(float _x, float _y, sf::Texture &_tex_sheet);
    virtual void update(const float &dt, const sf::Vector2f &mouse_pos_view) override;
    virtual void render(sf::RenderTarget &target, sf::Shader *shader = nullptr) override;

    void update_animation(const float &dt);
    void update_stamina();
    void update_attack();

    void lose_hp(const int hp);
    void lose_exp(const unsigned exp);

    void gain_hp(const int hp);
    void gain_exp(const unsigned exp);

    void run(const bool state);
    attribute_component *get_attribute_component();
    const bool get_running() const;
    const float &get_run_speed() const;

    virtual ~player();

private:
    bool attacking;
    bool running;
    float run_speed;

    sf::Texture weapon_texture;
    sf::Sprite weapon_sprite;

    sf::Clock run_time;

private:
    void init_variables();
};

#endif