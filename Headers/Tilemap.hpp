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

    /*@brief Initializes a tilemap with a saved file.*/
    tilemap(const std::string file_name);

    /* @brief Updates world border collision & tile collison with any given entity. */
    void update_collision(entity *entity, const float &dt);

    void update();

    /* @brief Renders the tilemap. Utilizes tile culling.
     *   @param target               Render target.
     *   @param grid_position        Used to cull tiles according to this position.
     *   @param shader               (Optional) Default value is nullptr.
     *   @param light_src            (Optional) Light source for the shaders. Default value is (0,0)
     *   @param show_collision       (Optinal) Whether to outline collidable tiles in red color. Mostly used in Editor state. Default value is false.
     */
    void render(sf::RenderTarget &target, const sf::Vector2i &grid_position,
                sf::Shader *shader = nullptr, const sf::Vector2f light_src = sf::Vector2f(),
                const bool show_collision = false);

    /*  @brief Saves tiles that should be rendered above the rest of the tilemap in a separate vector and renders them using this function.
     *   @param target                 Render target.
     *   @param shader                 (Optional) Default value is nullptr.
     *   @param light_src              (Optional) Light source for the shaders. Default value is (0,0)
     */
    void render_deferred(sf::RenderTarget &target, sf::Shader *shader = nullptr, const sf::Vector2f light_src = sf::Vector2f());

    /* @brief Takes three indicies from the mouse position in the grid and a tiles to that position if the internal tilemap array allows it .
    *   @param x               Grid position on the X axis for the new tile.
        @param y               Grid position on the Y axis for the new tile.
        @param layer           The number of layers on the X,Y position. (More than 5 layers will be ignored.)
        @param _rect           Int Recrangle for the sprite texture.
        @param collision       Whether the tile can be collided with or not.
        @param type            Type of the tile.
    */
    void add_tile(const unsigned x, const unsigned y, const unsigned layer, const sf::IntRect &_rect, const bool collision, const short type);

    /* @brief Removes a tile.
    *   @param x               Grid position on the X axis for the removed tile.
        @param y               Grid position on the Y axis for the removed tile.
        @param layer           Which tile layer to remove.
        @param type            Type of the tile. Only tiles with this given type can be removed.
    */
    void remove_tile(const unsigned x, const unsigned y, const unsigned layer, const short type);

    /*
        @brief Saves the entire tilemap to a text file.
        Format:
        Map parameters:
            ->Max size: X and Y
            ->Cell size (or grid size)
            ->Number of layers
            ->Texture sheet file name(string)

        Individual Tiles:
            ->Position: X and Y; Layer number; Texture rectangle; collision; tile type;

        @param file_name Name of the save file (Usually "savefile.sav").
    */
    void save_tilemap(const std::string file_name);

    /*@brief Loads the map from a file. If the file is not found, map loading is ignored.
     * @param file_name Name of the save file (Usually "savefile.sav").
     */
    void load_tilemap(const std::string file_name);

    const sf::Texture *get_tilesheet() const;

    const sf::Vector2i get_map_size_tiles() const;
    const sf::Vector2f get_map_size_pixels() const;

    const int get_num_of_layers(const sf::Vector2i mouse_pos_grid, const int layer) const;

    ~tilemap();

private:
    void init_textures();

    void update_worldborder_collision(entity *entity, const float &dt);

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