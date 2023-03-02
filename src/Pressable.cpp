#include "../Headers/pch.h"
#include "../Headers/GUI.hpp"

using namespace GUI;

pressable::pressable(){}

const bool pressable::is_pressable()
{
    if (key_timer.getElapsedTime().asMilliseconds() >
        key_time_max_miliseconds)
    {
        key_timer.restart();
        return true;
    }

    return false;
}

pressable::~pressable(){}