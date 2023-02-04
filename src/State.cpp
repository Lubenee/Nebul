#include "../Headers/pch.h"
#include "../Headers/State.hpp"

class state_data;
state::state(state_data *_state_data)
{
    state_details = _state_data;
    window = _state_data->window;
    gfx_settings = _state_data->gfx_settings;
    supported_keys = _state_data->supported_keys;
    states = _state_data->states;
    grid_size = _state_data->grid_size;
    quit = false;
    paused = false;
}

void state::update_mouse_pos()
{
    mouse_pos_screen = sf::Mouse::getPosition();
    mouse_pos_window = sf::Mouse::getPosition(*window);
    mouse_pos_view = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
}

const bool &state::get_quit() const
{
    return this->quit;
}

const bool state::pressable_button()
{
    if (key_timer.getElapsedTime().asMilliseconds() > key_time_max_miliseconds)
    {
        key_timer.restart();
        return true;
    }
    return false;
}

void state::set_pause(bool pause_state)
{
    paused = pause_state;
}

void state::end_state()
{
    quit = true;
}

state::~state()
{
}