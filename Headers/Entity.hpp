#ifndef ENTITY_H
#define ENTITY_H
#include "MovmentComponent.hpp"
#include "AnimationComponent.hpp"
#include "HitboxComponent.hpp"

class entity
{
public:
    entity();
    void set_texture(sf::Texture &_texture);
    void create_movment_component(const float max_velocity, const float _acceleration, const float _deceleration);
    void create_animation_component(sf::Texture &texture_sheet);
    void create_hitbox_component(float offset_x, float offset_y, float width, float height, sf::Sprite &_sprite);

    virtual void update(const float &dt);
    virtual void render(sf::RenderTarget &target);

    virtual void set_pos(const float _x, const float _y);
    virtual void move(const float _x, const float _y, const float &dt);

    virtual ~entity();

protected:
    sf::Texture *texture;
    sf::Sprite sprite;

    // Movment component
    movment_component *mc;

    // Animation component
    animation_component *ac;

    // Hitbox component
    hitbox_component *hc;

private:
};

#endif