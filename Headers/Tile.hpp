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

    void update();
    void render(sf::RenderTarget &target, sf::Shader *shader = nullptr, const sf::Vector2f player_pos = sf::Vector2f());

    const short get_type() const;
    const std::string get_as_string() const;
    const sf::Vector2f &get_pos() const;

    /* Returns whether the tile can be collided with or not. */
    const bool get_collision() const;
    const sf::FloatRect get_global_bounds() const;
    const sf::IntRect get_texture_rect() const;

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