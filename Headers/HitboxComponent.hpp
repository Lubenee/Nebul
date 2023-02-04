#ifndef HITBOX_COMPONENT_H
#define HITBOX_COMPONENT_H

class hitbox_component
{
public:
    hitbox_component(float offset_x, float offset_y, float width, float height, sf::Sprite &sprite);
    ~hitbox_component();

    void update();
    void render(sf::RenderTarget &target);

    bool intersects(const sf::FloatRect &rect);

private:
    sf::RectangleShape hitbox;
    sf::Sprite &sprite;

    sf::Vector2f offset;
};

#endif