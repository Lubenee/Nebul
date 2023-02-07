#ifndef HITBOX_COMPONENT_H
#define HITBOX_COMPONENT_H

class hitbox_component
{
public:
    hitbox_component(float offset_x, float offset_y, float width, float height, sf::Sprite &sprite);

    void update();
    void render(sf::RenderTarget &target);

    const sf::Vector2f &get_pos() const;

    void set_pos(const float _x, const float _y);
    void set_pos(const sf::Vector2f &_pos);

    const sf::FloatRect get_global_bounds() const;

    bool intersects(const sf::FloatRect &rect);

    ~hitbox_component();

private:
    sf::RectangleShape hitbox;
    sf::Sprite &sprite;

    sf::Vector2f offset;
};

#endif