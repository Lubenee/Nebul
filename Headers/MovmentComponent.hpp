#ifndef MOVMENT_COMPONENT_H
#define MOVMENT_COMPONENT_H

// Movment states
enum mov_states
{
    IDLE = 0,
    MOVING,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class movment_component
{
public:
    movment_component(sf::Sprite &sprite, const float _max_velocity, float _acc, float _dec);
    ~movment_component();

    /* @brief Decelerates the sprite and controls the maximum velocity. Moves the sprite.*/
    void update(const float &dt);
    void move(const float _x, const float _y, const float &dt, const float run_value = 1);

    /* @brief Reset the target's velocity. */
    void reset_velocity();
    /* @brief Reset the target's X velocity. */
    void reset_velocityX();
    /* @brief Reset the target's Y velocity. */
    void reset_velocityY();

    /* @brief Returns in what state the entity is in. (Idle, moving up, down, etc.)*/
    const bool get_state(const short unsigned state) const;
    /* @brief Returns the velocity. */
    sf::Vector2f &get_velocity();
    /* @brief Retuns the maximum velocity. */
    const float &get_max_velocity() const;

private:
    sf::Sprite &sprite;

    float max_velocity;
    const float max_velocity_copy;
    sf::Vector2f velocity;
    float acceleration;
    float deceleration;
};

#endif