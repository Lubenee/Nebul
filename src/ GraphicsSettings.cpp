#include "../Headers/pch.h"
#include "../Headers/GraphicsSettings.hpp"

graphics_settings::graphics_settings()
{
    title = "Default";
    resolution = sf::VideoMode::getDesktopMode();
    fullscreen = false;
    vsync = false;
    framerate_limit = 120;
    cs.antialiasingLevel = 0;
    vm = sf::VideoMode::getFullscreenModes();
}

void graphics_settings::load_from_file(const std::string path)
{
    std::ifstream ifs;
    ifs.open(path.c_str(), std::ios::in);
    if (ifs.is_open())
    {
        std::getline(ifs, title);
        ifs >> resolution.width >> resolution.height;
        ifs >> fullscreen;
        ifs >> framerate_limit;
        ifs >> vsync;
        ifs >> cs.antialiasingLevel;
    }
    ifs.close();
}

void graphics_settings::save_to_file(const std::string path)
{
    std::ofstream ofs;
    ofs.open(path.c_str(), std::ios::out);
    if (ofs.is_open())
    {
        ofs << title << '\n';
        ofs << resolution.width << ' ' << resolution.height << '\n';
        ofs << fullscreen << '\n';
        ofs << framerate_limit << '\n';
        ofs << vsync << '\n';
        ofs << cs.antialiasingLevel << '\n';
    }
    ofs.close();
}