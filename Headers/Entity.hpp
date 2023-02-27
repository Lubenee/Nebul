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

    /*  @brief Pure virtual update function.*/
    virtual void update(const float &dt, const sf::Vector2f &mouse_pos_view) = 0;

    /*  @brief Pure virtual render function.*/
    virtual void render(sf::RenderTarget &target, sf::Shader *shader = nullptr) = 0;

    /*  @brief Sets the entity's position. If the entity's hitbox component is initialized, the hitbox is moved instead. */
    virtual void set_pos(const float _x, const float _y);

    /*  @brief Moves the entity. If the entity's movment component is initialized, it's move function is used instead.
     *     @param x           New X axis position.
     *     @param Y           New Y axis position.
     *     @param delta_time  Needed for calculations.
     *     @param run_value   The entity's max velocity is multiplied by this
     */
    virtual void move(const float _x, const float _y, const float &dt, const float run_value = 1);

    /*  @brief Returns the entity's position.  */
    virtual const sf::Vector2f &get_pos() const;

    /*  @brief Returns the entity sprite's center. If the entity has a hitbox component, the hitbox's center is returned. */
    virtual const sf::Vector2f get_center() const;

    /*  @brief Returns the entity's global bounds.  */
    virtual const sf::FloatRect get_global_bounds() const;

    /*  @brief Returns the entity's position relative to the map grid. */
    virtual const sf::Vector2i get_gridpos(const int grid_size) const;

    /*  @brief Returns the coordinates of the entity's next position. */
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