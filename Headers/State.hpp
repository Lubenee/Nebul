#ifndef STATE_H
#define STATE_H
#include "Player.hpp"
#include "GUI.hpp"
#include "GraphicsSettings.hpp"

class player;
class graphics_settings;
class state_data;

class state
{
public:
    state(state_data *_state_data);

    virtual void update(const float &dt) = 0;
    virtual void render(sf::RenderTarget *target = nullptr) = 0;

    const bool &get_quit() const;
    const bool pressable_button();

    void set_pause(bool pause_state);

    void end_state();
    virtual ~state();

protected:
    virtual void init_keybinds() = 0;
    virtual void update_mouse_pos();

protected:
    /* Mouse pos */
    sf::Vector2i mouse_pos_screen;
    sf::Vector2i mouse_pos_window;
    sf::Vector2f mouse_pos_view;

    /* Resources */
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, int> keybinds;

    state_data *state_details;

    // TODO
    // These should probably be private but im too lazy to use the accessors
protected:
    sf::RenderWindow *window;

    bool paused;
    bool quit;

    static const sf::Int32 key_time_max_miliseconds = 450;
    sf::Clock key_timer;

    std::map<std::string, int> *supported_keys;
    graphics_settings *gfx_settings;

    std::stack<state *> *states;
    float grid_size;
};

/* Used to more efficiently send data between each state. */
class state_data
{
public:
    state_data() = default;

    sf::RenderWindow *window;
    graphics_settings *gfx_settings;
    std::map<std::string, int> *supported_keys;
    std::stack<state *> *states;
    float grid_size;
};

#endif
