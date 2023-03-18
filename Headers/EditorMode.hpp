#ifndef EDITOR_MODE_H
#define EDITOR_MODE_H
#include "State.hpp"
#include "Tilemap.hpp"
#include "GUI.hpp"

struct editor_state_data
{
public:
    std::map<std::string, int> *keybinds;

    sf::View *view;

    sf::Vector2i *mouse_pos_screen;
    sf::Vector2i *mouse_pos_window;
    sf::Vector2f *mouse_pos_view;
    sf::Vector2i *mouse_pos_grid;

    sf::Vector2f *map_size;

    sf::Font *font;
};

class editor_mode
{
public:
    editor_mode(state_data *state_details, tilemap *map, editor_state_data *editor_details);

    virtual void update(const float &dt) = 0;
    virtual void render(sf::RenderTarget *target = nullptr) = 0;

    virtual ~editor_mode();

private:
    virtual void update_gui(const float &dt) = 0;
    virtual void update_input(const float &dt) = 0;

    virtual void render_gui(sf::RenderTarget &target) = 0;

protected:
    const bool pressable_button(const int modifier = 0);

protected:
    state_data *state_details;
    editor_state_data *editor_details;
    tilemap *map;

    static const sf::Int32 key_time_max_miliseconds = 350;
    sf::Clock key_timer;
};

#endif //! EDITOR_MODE_H