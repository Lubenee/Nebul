#ifndef ENEMY_H
#define ENEMY_H
#include "Entity.hpp"

class enemy : public entity
{
public:
    enemy(float _x, float _y, sf::Texture &_tex_sheet);

    virtual void update(const float &dt, const sf::Vector2f &mouse_pos_view) override;
    virtual void render(sf::RenderTarget &target, sf::Shader *shader = nullptr) override;

    void update_animations(const float &dt);

    virtual ~enemy();

private:
};

#endif //! ENEMY_H