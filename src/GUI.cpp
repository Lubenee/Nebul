#include "../Headers/pch.h"
#include "../Headers/GUI.hpp"

const float GUI::p2p_x(const float _percent, const sf::VideoMode &vm)
{
    return std::floor(static_cast<float>(vm.width) * (_percent / 100.f));
}

const float GUI::p2p_y(const float _percent, const sf::VideoMode &vm)
{
    return std::floor(static_cast<float>(vm.height) * (_percent / 100.f));
}

const unsigned GUI::calc_char_size(const sf::VideoMode &vm)
{
    return static_cast<unsigned>((vm.width + vm.height) / 50);
}