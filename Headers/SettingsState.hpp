#ifndef SETTINGS_STATE_H
#define SETTINGS_STATE_H

#include "State.hpp"
class settings_state : public state
{
public:
    settings_state(state_data *_state_data);
    /*
     *   @brief Clears the GUI elements, re-initializing the GUI to retain element positions when switching between resolutions.
     */
    void reset_gui();

    /* @brief Renders any GUI related compoments that the class has.*/
    void update_gui();

    /*  @brief In order to avoid clicking on a drop menu button and then
        accidentally activating some regular button behind it,
        this timer checks if enough time has passed after selecting something
        from the drop menu.
    */
    void update_collision_timer();

    bool valid_button_collision();

    /* @brief Gives different buttons' functionality. */
    void button_handler();
    void update(const float &dt) override;

    void render(sf::RenderTarget *target = nullptr) override;

    /* @brief Renders any GUI related compoments that the class has.*/
    void render_gui(sf::RenderTarget &target);

    virtual ~settings_state();

private:
    void init_keybinds();
    void init_fonts();
    void init_background();
    void init_gui();

private:
    sf::RectangleShape background;
    sf::Texture background_texture;
    sf::Font font;

    std::map<std::string, GUI::pressable *> buttons;

    /* @brief In order to avoid clicking on a drop menu button and then
        accidentally activating some regular button behind it,
        this timer checks if enough time has passed after selecting something
        from the drop menu.
    */
    sf::Clock button_collision_timer;

    sf::Text options_text;

    std::vector<sf::VideoMode> vms;
};

#endif
