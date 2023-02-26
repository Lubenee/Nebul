#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "State.hpp"
#include "PauseMenu.hpp"
#include "Tilemap.hpp"
#include "PlayerGUI.hpp"

class state;
class pause_menu;
class tilemap;

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
    void init_player_gui();
    void init_map();
    void init_pause_menu();
    void init_view();
    void init_render_canvas();
    void init_shaders();

    void update_view(const float &dt);
    void update_input(const float &dt);
    void update_player_input(const float &dt);
    void update_player_gui(const float &dt);
    void update_menu_buttons();
    void update_tilemap(const float &dt);

private:
    sf::View view;
    sf::Vector2i view_grid_pos;

    /* To remove weird texture glitching and make rendering smoother, everything in the game is first drawn on this sort of canvas texture,
    and then gets pasted on the screen all at once.*/
    sf::RenderTexture render_texture;

    /* This sprite "holds" our canvas. */
    sf::Sprite render_sprite;

    sf::Shader core_shader;

    tilemap *map;
    player *plr;
    player_gui *plr_gui;

    sf::Font p_menu_font;
    pause_menu *p_menu;
};

#endif