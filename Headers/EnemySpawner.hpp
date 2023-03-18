#ifndef ENEMY_SPAWNER_H
#define ENEMY_SPAWNER_H
#include "Tile.hpp"

class enemy_spawner : public tile
{
public:
    enemy_spawner(size_t x, size_t y, float grid_size, sf::Texture &_tex, const sf::IntRect &_rect,
                  int enemy_type, int amount, int time_to_spawn, float max_distance);

    void update();

    void render(sf::RenderTarget &target);

    virtual ~enemy_spawner();

private:
    int enemy_type;
    int spawn_amount;
    float time_to_spawn;

    /* How much distance the enemy can travel before despawning. (If there isn't a player nearby).*/
    float max_distance;
};

#endif //! ENEMY_SPAWNER_H