#ifndef PAUSE_MENU_H
#define PAUSE_MENU_H
#include "GUI.hpp"

class pause_menu
{

public:
    pause_menu(sf::RenderWindow &window, sf::Font &_font);

    void update(const sf::Vector2f &mouse_pos);
    void render(sf::RenderTarget &target);

    std::map<std::string, GUI::button *> &get_buttons();
    void add_button(const std::string &key, float y, const std::string &text);
    const bool is_button_pressed(const std::string key) const;

    ~pause_menu();

protected:
    void init_buttons();

private:
    sf::RectangleShape background;
    sf::RectangleShape container;
    std::map<std::string, GUI::button *> buttons;

    sf::Font &font;
    sf::Text text;
};

#endif