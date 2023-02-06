#ifndef TILEMAP_H
#define TILEMAP_H
#include "Tile.hpp"

class tilemap
{
public:
    tilemap(float _grid_size, unsigned width, unsigned height, const std::string texture_file);

    void update();
    void render(sf::RenderTarget &target);

    /* Takes three indicies from the mouse position in the grid and a tiles to that position if the internal tilemap array allows it .*/
    void add_tile(const unsigned x, const unsigned y, const unsigned layer, const sf::IntRect &_rect, const bool &collision, const short &type);
    void remove_tile(const unsigned x, const unsigned y, const unsigned layer, const short &type);

    /*
        Saves the entire tilemap to a text file.
        Format:
        Map parameters:
            ->Max size: X and Y
            ->Cell size (or grid size)
            ->Number of layers
            ->Texture sheet file name(string)

        Individual Tiles:
            ->Position: X and Y; Layer number; Texture rectangle; collision; tile type;
    */
    void save_tilemap(const std::string file_name);
    void load_tilemap(const std::string file_name);

    const sf::Texture *get_tilesheet() const;
    void clear_map();

    ~tilemap();

private:
    void init_textures();

private:
    std::vector<std::vector<std::vector<tile *>>> map;
    sf::Vector2u map_size;

    sf::Texture tile_sheet;
    std::string texture_file;

    unsigned layers;
    unsigned grid_sizeu;
    float grid_sizef;
};

#endif