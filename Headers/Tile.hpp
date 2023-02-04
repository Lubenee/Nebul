#ifndef TILE_H
#define TILE_H


class tile
{
public:
    tile() = default;
    tile(float x, float y, float grid_size);

    void update();
    void render(sf::RenderTarget& target);


    virtual ~tile();

protected:
    sf::RectangleShape shape;

private:
};

#endif