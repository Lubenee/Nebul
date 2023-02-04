#include "../Headers/pch.h"
#include "../Headers/Tilemap.hpp"

tilemap::tilemap(float _grid_size, unsigned width, unsigned height)
{
    map_size.x = width;
    map_size.y = height;
    layers = 1;

    grid_sizef = _grid_size;
    grid_sizeu = static_cast<unsigned>(grid_sizef);

    map.resize(map_size.x);

    for (size_t x = 0; x < map_size.x; ++x)
    {
        map.push_back(std::vector<std::vector<tile>>());
        for (size_t y = 0; y < map_size.y; ++y)
        {
            map[x].resize(map_size.y);
            map[x].push_back(std::vector<tile>());
            for (size_t z = 0; z < layers; ++z)
            {
                map[x][y].resize(layers);
                map[x][y].push_back(tile((float)x * grid_sizef, (float)y * grid_sizef, grid_sizef));
            }
        }
    }
}

void tilemap::update() {}

void tilemap::render(sf::RenderTarget &target)
{
    for (auto &x : map)
        for (auto &y : x)
            for (auto &tile : y)
                tile.render(target);
}

void tilemap::add_tile() {}

void tilemap::remove_tile() {}

tilemap::~tilemap() {}