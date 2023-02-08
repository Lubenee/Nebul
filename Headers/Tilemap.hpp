#ifndef TILEMAP_H
#define TILEMAP_H
#include "Tile.hpp"
#include "Entity.hpp"

class entity;
class tile;

class tilemap
{
public:
    tilemap(float _grid_size, int width, int height, const std::string texture_file);

    /* Updates world border collision & tile collison with any given entity. */
    void update_collision(entity *entity, const float &dt);

    void update();
    void render(sf::RenderTarget &target, const sf::Vector2i &grid_position);
    void render_deferred(sf::RenderTarget &target);

    /* Takes three indicies from the mouse position in the grid and a tiles to that position if the internal tilemap array allows it .*/
    void add_tile(const unsigned x, const unsigned y, const unsigned layer, const sf::IntRect &_rect, const bool collision, const short type);
    void remove_tile(const unsigned x, const unsigned y, const unsigned layer, const short type);

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
    const int get_num_of_layers(const sf::Vector2i mouse_pos_grid, const int layer) const;

    ~tilemap();

private:
    void init_textures();

    void update_worldborder_collision(entity *entity);

    void clear_map();

private:
    std::vector<std::vector<std::vector<std::vector<tile *>>>> map;
    sf::Vector2i map_size_tiles;
    sf::Vector2f map_size_pixels;

    sf::Texture tile_sheet;
    std::string texture_file;
    std::stack<tile *> deferred_render_stack;

    unsigned layers;
    unsigned grid_sizeu;
    float grid_sizef;
    sf::RectangleShape collision_box;

    // Culling
    int from_x, to_x;
    int from_y, to_y;
    int layer;
};

#endif