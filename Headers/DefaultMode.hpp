#ifndef DEFAULT_MODE_H
#define DEFAULT_MODE_H
#include "EditorMode.hpp"

class default_mode : public editor_mode
{
public:
    default_mode(state_data *_state_data, tilemap *map, editor_state_data *editor_details);

    virtual void update(const float &dt);
    virtual void render(sf::RenderTarget *target = nullptr);

    virtual ~default_mode();

private:
    void init_variables();
    void init_gui();

    virtual void update_gui(const float &dt);
    virtual void update_input(const float &dt);

    virtual void render_gui(sf::RenderTarget &target);

private:
    sf::Text mouse_text;
    sf::RectangleShape sidebar;

    sf::RectangleShape selector;
    GUI::texture_selector *tex_selector;
    sf::IntRect texture_rect;

    static const unsigned mouse_text_offset = 60;

    bool tile_collision;
    short tile_type;

    int tile_layers;
};

#endif //! DEFAULT_MODE_H