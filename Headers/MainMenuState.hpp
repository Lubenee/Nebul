#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H
#include "GameState.hpp"
#include "EditorState.hpp"
#include "SettingsState.hpp"

class game_state;
class editor_state;
class settings_state;

class main_menu_state : public state
{
public:
    main_menu_state(state_data* state_data);
    void init_keybinds();
    void init_fonts();
    void init_buttons();
    void init_background();


    void update_input(const float &dt);
    void update_buttons();
    void button_handler();
    void update(const float &dt);

    void render_buttons(sf::RenderTarget &target);
    void render(sf::RenderTarget *target = nullptr);

    virtual ~main_menu_state();

private:
    sf::RectangleShape background;
    sf::Texture background_texture;
    sf::Font font;

    std::map<std::string, GUI::button *> buttons;

};

#endif