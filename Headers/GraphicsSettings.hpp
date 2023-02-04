#ifndef GRAPHICS_SETTINGS_H
#define GRAPHICS_SETTINGS_H

class graphics_settings
{
public:
    graphics_settings();

    void load_from_file(const std::string path);

    void save_to_file(const std::string path);

    std::string title;
    sf::VideoMode resolution;
    bool fullscreen;
    bool vsync;
    size_t framerate_limit;
    sf::ContextSettings cs;
    std::vector<sf::VideoMode> vm;

    ~graphics_settings() = default;
};

#endif