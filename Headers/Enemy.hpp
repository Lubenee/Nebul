#ifndef ENEMY_H
#define ENEMY_H
#include "Entity.hpp"
#include "EnemySpawner.hpp"

class enemy : public entity
{
public:
    enemy(float _x, float _y, sf::Texture &_tex_sheet, enemy_spawner &_spawner);

    virtual void update(const float &dt, const sf::Vector2f &mouse_pos_view) override;
    virtual void render(sf::RenderTarget &target, sf::Shader *shader = nullptr) override;

    virtual ~enemy();

private:
    void update_animations(const float &dt);

private:
    enemy_spawner &spawner;
};

#endif //! ENEMY_H