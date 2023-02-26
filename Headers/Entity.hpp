#ifndef ENTITY_H
#define ENTITY_H
#include "MovmentComponent.hpp"
#include "AnimationComponent.hpp"
#include "HitboxComponent.hpp"
#include "AttributeComponent.hpp"

/* Entity abstract class made to house all sorts of entites, including but not limited to players, enemies, npc, etc.*/

class entity
{
public:
    entity();

    /*@brief Sets the entity's texture.
     *   @param _texture This texture is applied to the entity's sprite. This class is not responsible for freeing this memory, the user must do it someplace else.
     */
    void set_texture(sf::Texture &_texture);

    /*  @brief Creates a movment component for the entity. If left uninitialized, the default value is nullptr.
     *       @param max_velocity             The entity's maximum velocity.
     *       @param acceleration             The entity's speed acceleration.
     *       @param deceleration             The entity's speed deceleration.
     */
    void create_movment_component(const float max_velocity, const float _acceleration, const float _deceleration);

    /*  @brief Creates an animation component for the entity. If left uninitialized, the default value is nullptr.
     *       @param texture_sheet            A sheet of sprites for the entity's animation. A single animation component is able to handle multiple animations.
     */
    void create_animation_component(sf::Texture &texture_sheet);

    /*  @brief Creates a hitbox component for the entity. If left uninitialized, the default value is nullptr.
     */
    void create_hitbox_component(float offset_x, float offset_y, float width, float height, sf::Sprite &_sprite);

    /*  @brief Creates an attribute component for the entity. Will be mostly used for user-playable characters. Handles all sorts of different attributes (Health, Experience, ..). If left uninitialized, the default value is nullptr.
     *       @param level Starting level.
     */
    void create_attribute_component(const int _level);

    virtual void update(const float &dt, const sf::Vector2f &mouse_pos_view) = 0;
    virtual void render(sf::RenderTarget &target, sf::Shader *shader = nullptr) = 0;

    virtual void set_pos(const float _x, const float _y);
    virtual void move(const float _x, const float _y, const float &dt, const float run_value = 1);

    virtual const sf::Vector2f &get_pos() const;
    virtual const sf::Vector2f get_center() const;
    virtual const sf::FloatRect get_global_bounds() const;
    virtual const sf::Vector2i get_gridpos(const int grid_size) const;
    virtual const sf::FloatRect get_next_pos(const float &dt) const;

    virtual void reset_velocity();
    virtual void reset_velocityX();
    virtual void reset_velocityY();

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

    // Attribute component
    attribute_component *at_c;

private:
};

#endif