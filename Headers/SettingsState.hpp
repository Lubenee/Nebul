#ifndef SETTINGS_STATE_H
#define SETTINGS_STATE_H

#include "State.hpp"
class settings_state : public state
{
public:
    settings_state(state_data* _state_data);
    void init_keybinds();
    void init_fonts();
    void init_background();
    void init_gui();
    void init_text();

    /* Renders any GUI related compoments that the class has.*/
    void update_gui();
    void update_input(const float &dt);

    /* Gives different buttons functionality. */
    void button_handler();
    void update(const float &dt);

    void render(sf::RenderTarget *target = nullptr);

    /* Renders any GUI related compoments that the class has.*/
    void render_gui(sf::RenderTarget &target);

    virtual ~settings_state();

private:
    sf::RectangleShape background;
    sf::Texture background_texture;
    sf::Font font;

    std::map<std::string, GUI::button *> buttons;
    std::map<std::string, GUI::drop_down_box *> drop_lists;

    sf::Text options_text;

    std::vector<sf::VideoMode> vms;
};

#endif
