#ifndef EDITOR_STATE_H
#define EDITOR_STATE_H
#include "State.hpp"
#include "Tilemap.hpp"
#include "PauseMenu.hpp"

class editor_state : public state
{
public:
    editor_state(state_data *_state_data);

    void update(const float &dt);
    void render(sf::RenderTarget *target = nullptr);

    virtual ~editor_state();

private:
    void init_keybinds();
    void init_fonts();
    void init_buttons();
    void init_text();
    void init_background();
    void init_tilemap();
    void init_pause_menu();
    void init_gui();
    void init_view();

    void update_gui();
    void update_input(const float &dt);
    void update_buttons();
    void update_editor_input();
    void button_handler();
    void update_pause_menu();

    void render_buttons(sf::RenderTarget &target);
    void render_gui(sf::RenderTarget &target);

private:
    sf::Font font;
    sf::Text mouse_text;
    static const unsigned mouse_text_offset = 60;

    tilemap *map;
    sf::IntRect texture_rect;
    bool tile_collision;
    short tile_type;

    GUI::max_press_time pt;
    std::map<std::string, GUI::button *> buttons;
    pause_menu *p_menu;

    sf::RectangleShape selector;
    GUI::texture_selector *tex_selector;
    sf::RectangleShape sidebar;

    sf::View view;
    const float cam_speed;
};

#endif