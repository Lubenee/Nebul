#ifndef PLAYERGUI_H
#define PLAYERGUI_H
#include "Player.hpp"
#include "GUI.hpp"
class player;

class player_gui
{
public:
    player_gui(player *_player, sf::VideoMode &vm);

    void update(const float &dt);
    void render(sf::RenderTarget &target);

    ~player_gui();

private:
    void init_font();

    void init_hp_bar();
    void init_exp_bar();
    void init_stamina_bar();
    void init_level_bar();

    void update_hp_bar();
    void update_exp_bar();
    void update_stamina_bar();
    void update_level_bar();

    void render_hp_bar(sf::RenderTarget &target);
    void render_exp_bar(sf::RenderTarget &target);
    void render_stamina_bar(sf::RenderTarget &target);
    void render_level_bar(sf::RenderTarget &target);

private:
    player *plr;

    sf::VideoMode &vm;
    sf::Font font;

    /* Health Bar. */
    std::string hp_bar_string;
    sf::Text hp_bar_text;
    float hp_bar_max_size;
    sf::RectangleShape hp_bar_back;
    sf::RectangleShape hp_bar_inner;

    /* Experience Bar. */
    std::string exp_bar_string;
    sf::Text exp_bar_text;
    float exp_bar_max_size;
    sf::RectangleShape exp_bar_back;
    sf::RectangleShape exp_bar_inner;

    /* Stamina Bar. */
    std::string stamina_bar_string;
    sf::Text stamina_bar_text;
    float stamina_bar_max_size;
    sf::RectangleShape stamina_bar_back;
    sf::RectangleShape stamina_bar_inner;

    /* Level Bar. */
    std::string level_bar_string;
    sf::Text level_bar_text;
    sf::RectangleShape level_bar_back;
};

#endif