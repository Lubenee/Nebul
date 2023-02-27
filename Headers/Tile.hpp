#ifndef TILE_H
#define TILE_H

// Tile types
enum tt
{
    DEFAULT = 0,
    DAMAGING,
    ABOVE_PLAYER

};

class tile
{
public:
    tile();
    tile(size_t x, size_t y, float grid_size, sf::Texture &_tex, const sf::IntRect &_rect,
         bool collision = false, short type = tt::DEFAULT);

    /*  @brief Used to update the tile, if it needs updating. */
    void update();
    /*  @brief Renders the tile.
     *       @param target       Render target.
     *       @param shader       (Optional) Nullptr value if not passed.
     *       @param light_src    (Optional) Light source for shaders.
     */
    void render(sf::RenderTarget &target, sf::Shader *shader = nullptr, const sf::Vector2f light_src = sf::Vector2f());

    /*  @brief Returns the tile's type. */
    const short get_type() const;

    /*  @brief Retuns the tile's information. Usually used for saving to files. */
    const std::string get_as_string() const;

    /*  @brief Returns the tile's position relative to the window. */
    const sf::Vector2f &get_pos() const;

    /*  @brief Returns whether the tile can be collided with or not. */
    const bool get_collision() const;

    /*  @brief Returns the tile's global bounds. */
    const sf::FloatRect get_global_bounds() const;

    /*  @brief Returns the tile's texture rectangle. */
    const sf::IntRect get_texture_rect() const;

    /*  @brief Checks for intersection.
    *       @param bounds Float Rectangle of another body.
    */
    const bool intersects(const sf::FloatRect &_bounds) const;

    friend std::ostream &operator<<(std::ostream &os, const tile &tile);
    virtual ~tile();

protected:
    sf::Sprite shape;
    sf::IntRect texture_rect;
    bool collision;
    short type;

private:
};

#endif