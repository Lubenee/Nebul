#ifndef ITEM_H
#define ITEM_H

class item
{
public:
    item();
    ~item();

    void update();
    void render(sf::RenderTarget &target);

private:
};

#endif