#ifndef PLAYERGUI_H
#define PLAYERGUI_H
#include "Player.hpp"
class player;

class player_gui
{
public:
    player_gui(player *_player);

    void update(const float &dt);
    void render(sf::RenderTarget &target);

    ~player_gui();

private:
    void init_font();
    void init_hp_bar();

    void update_hp_bar();

    void render_hp_bar(sf::RenderTarget &target);

private:
    player *plr;

    sf::Font font;

    /* HP Bar. */
    std::string hp_bar_string;
    sf::Text hp_bar_text;
    float hp_bar_max_size;
    sf::RectangleShape hp_bar_back;
    sf::RectangleShape hp_bar_inner;
};

#endif