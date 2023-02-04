#ifndef TILEMAP_H
#define TILEMAP_H
#include "Tile.hpp"

class tilemap
{
public:
    tilemap(float _grid_size, unsigned width, unsigned height );

    void update();
    void render(sf::RenderTarget& target);

    void add_tile();
    void remove_tile();
    
    ~tilemap();
private:
    std::vector<std::vector<std::vector<tile>>> map;
    sf::Vector2u map_size;

    unsigned layers;
    unsigned grid_sizeu;
    float grid_sizef;
};

#endif