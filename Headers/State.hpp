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

    /*
    * @brief
        Converts a percentage value to pixels relative to the current resolution on the x-axis.
      @param        float percent       The percentage value.
      @retval       const float         The calculated pixel value.
    */
    const float p2p_x(const float _percent);

    /*
    * @brief
        Converts a percentage value to pixels relative to the current resolution on the y-axis.
      @param        float percent       The percentage value.
      @retval       float pixels         Returns the calculated pixel value.
    */
    const float p2p_y(const float _percent);

    const bool &get_quit() const;
    const bool pressable_button();
    const bool pressable_button_short();

    void set_pause(bool pause_state);

    void end_state();
    virtual ~state();

protected:
    virtual void init_keybinds() = 0;
    virtual void update_mouse_pos(const sf::View *view = nullptr);

protected:
    /* Mouse pos */
    sf::Vector2i mouse_pos_screen;
    sf::Vector2i mouse_pos_window;
    sf::Vector2f mouse_pos_view;
    sf::Vector2i mouse_pos_grid;

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

    static const sf::Int32 key_time_max_miliseconds = 350;
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
