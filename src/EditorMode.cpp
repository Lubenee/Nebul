#include "../Headers/pch.h"
#include "../Headers/EditorMode.hpp"

editor_mode::editor_mode(state_data *state_details, tilemap *map, editor_state_data *editor_details)
    : state_details(state_details), map(map), editor_details(editor_details)
{
}

const bool editor_mode::pressable_button(const int modifier)
{
    if (key_timer.getElapsedTime().asMilliseconds() > key_time_max_miliseconds - modifier)
    {
        key_timer.restart();
        return true;
    }
    return false;
}

editor_mode::~editor_mode() {}