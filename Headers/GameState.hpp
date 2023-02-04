#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "State.hpp"
#include "PauseMenu.hpp"
#include "Tilemap.hpp"

class game_state : public state
{
public:
    game_state(state_data *_state_data);

    void update(const float &dt);
    void render(sf::RenderTarget *target);

    virtual ~game_state();

private:
    void init_keybinds();
    void init_assets();
    void init_player();
    void init_map();
    void init_pause_menu();

    void update_input(const float &dt);
    void update_player_input(const float &dt);
    void update_menu_buttons();

private:
    tilemap *map;
    player *plr;

    sf::Font p_menu_font;
    pause_menu *p_menu;
};

#endif