#ifndef TILEMAP_H
#define TILEMAP_H
#include "Tile.hpp"

class tilemap
{
public:
    tilemap(float _grid_size, unsigned width, unsigned height);

    void update();
    void render(sf::RenderTarget &target);

    /* Takes three indicies from the mouse position in the grid and a tiles to that position if the internal tilemap array allows it .*/
    void add_tile(const unsigned x, const unsigned y, const unsigned layer, const sf::IntRect &_rect);
    void remove_tile(const unsigned x, const unsigned y, const unsigned layer);

    const sf::Texture *get_tilesheet() const;

    ~tilemap();

private:
    void init_textures();

private:
    std::vector<std::vector<std::vector<tile *>>> map;
    sf::Vector2u map_size;

    sf::Texture tile_sheet;

    unsigned layers;
    unsigned grid_sizeu;
    float grid_sizef;
};

#endif