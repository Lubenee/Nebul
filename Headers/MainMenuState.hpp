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
    main_menu_state(state_data *state_data);

    /* @brief Updates the main menu state events. */
    void update(const float &dt);

    /* @brief Renders the main menu state events. */
    void render(sf::RenderTarget *target = nullptr);

    virtual ~main_menu_state();

private:
    void init_keybinds();
    void init_fonts();
    void init_gui();
    void init_background();

    void reset_gui();

    void update_input(const float &dt);
    void update_buttons();
    void button_handler();

    void render_buttons(sf::RenderTarget &target);

private:
    sf::RectangleShape background;
    sf::Texture background_texture;
    sf::Font font;

    std::map<std::string, GUI::button *> buttons;
};

#endif