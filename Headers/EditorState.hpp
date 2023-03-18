#ifndef EDITOR_STATE_H
#define EDITOR_STATE_H
#include "State.hpp"
#include "Tilemap.hpp"
#include "PauseMenu.hpp"
#include "DefaultMode.hpp"

// Editor Modes
enum em
{
    DEFAULT_MODE = 0,
    ENEMY_MODE
};

class editor_state : public state
{
public:
    editor_state(state_data *_state_data);

    void update(const float &dt);
    void render(sf::RenderTarget *target = nullptr);

    virtual ~editor_state();

private:
    void init_modes();

    void init_editor_data();
    void init_keybinds();
    void init_fonts();
    void init_tilemap();
    void init_pause_menu();
    void init_view();

    void update_input(const float &dt);
    void button_handler();
    void update_pause_menu();
    void update_modes(const float &dt);

    void render_modes(sf::RenderTarget &target);

private:
    sf::Font font;
    sf::Text mouse_text;

    tilemap *map;
    sf::Vector2f map_size;

    pause_menu *p_menu;

    sf::View view;
    const float cam_speed;

    std::vector<editor_mode *> modes;

    editor_state_data editor_details;
};

#endif