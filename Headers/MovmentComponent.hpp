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

    /* Decelerates the sprite and controls the maximum velocity. Moves the sprite.*/
    void update(const float &dt);
    void move(const float _x, const float _y, const float &dt, const float run_value = 1);

    /* Reset the target's velocity. */
    void reset_velocity();
    void reset_velocityX();
    void reset_velocityY();

    const bool get_state(const short unsigned state) const;
    sf::Vector2f &get_velocity();
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