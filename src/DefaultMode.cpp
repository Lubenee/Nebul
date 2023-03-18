#include "../Headers/pch.h"
#include "../Headers/DefaultMode.hpp"

default_mode::default_mode(state_data *_state_data, tilemap *map, editor_state_data *editor_details)
    : editor_mode(_state_data, map, editor_details)
{
    init_variables();
    init_gui();
}

void default_mode::init_gui()
{
    // Text
    mouse_text.setFont(*editor_details->font);
    mouse_text.setCharacterSize(10);
    mouse_text.setFillColor(sf::Color::White);

    // General gui
    sidebar.setSize(sf::Vector2f(80.f, static_cast<float>(state_details->gfx_settings->resolution.height)));
    sidebar.setFillColor(sf::Color(50, 50, 50, 100));
    sidebar.setOutlineColor(sf::Color(200, 200, 200, 150));
    sidebar.setOutlineThickness(-1.f);

    selector.setFillColor(sf::Color(200, 200, 200, 125));
    selector.setSize(sf::Vector2f(state_details->grid_size, state_details->grid_size));
    selector.setOutlineThickness(-1.f);
    selector.setOutlineColor(sf::Color(50, 200, 20, 255));
    selector.setTexture(map->get_tilesheet());

    tex_selector = new GUI::texture_selector(20.f, 20.f, 640.f, 256.f, state_details->grid_size, *(map->get_tilesheet()), *editor_details->font);
}

void default_mode::init_variables()
{
    tile_collision = false;
    tile_layers = 0;
    tile_type = tt::DEFAULT;
    texture_rect = sf::IntRect(200, 0, static_cast<int>(state_details->grid_size), static_cast<int>(state_details->grid_size));
}

void default_mode::update_gui(const float &dt)
{
    tex_selector->update(*editor_details->mouse_pos_window);
    if (!tex_selector->get_active())
    // for snappy selection
    {
        selector.setPosition(editor_details->mouse_pos_grid->x * state_details->grid_size, editor_details->mouse_pos_grid->y * state_details->grid_size);
        selector.setTextureRect(texture_rect);
    }

    mouse_text.setPosition(editor_details->mouse_pos_view->x - mouse_text_offset, editor_details->mouse_pos_view->y);
    std::stringstream ss;

    /* This check prevents a crash where the layers/collision return undefined when the mouse goes out of the world borders. */
    if (editor_details->mouse_pos_grid->x >= 0 && editor_details->mouse_pos_grid->x < editor_details->map_size->x &&
        editor_details->mouse_pos_grid->y >= 0 && editor_details->mouse_pos_grid->y < editor_details->map_size->y)
    {
        ss << editor_details->mouse_pos_grid->x << ' ' << editor_details->mouse_pos_grid->y << '\n'
           << texture_rect.left << ' ' << texture_rect.top << '\n'
           << "Collision: " << tile_collision << '\n'
           << "Type: " << tile_type << '\n'
           << "Layers: " << map->get_num_of_layers(*editor_details->mouse_pos_grid, tile_layers);
    }
    else
    {
        ss << editor_details->mouse_pos_grid->x << ' ' << editor_details->mouse_pos_grid->y << '\n';
    }
    mouse_text.setString(ss.str());
}

void default_mode::update_input(const float &dt)
{
    // Add a new tile
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (!sidebar.getGlobalBounds().contains(sf::Vector2f(*editor_details->mouse_pos_view)))
        {
            if (!tex_selector->get_active())
                map->add_tile(editor_details->mouse_pos_grid->x, editor_details->mouse_pos_grid->y, 0, texture_rect, tile_collision, tile_type);
            else
                texture_rect = tex_selector->get_texture_rect();
        }
    }
    // Remove a tile
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && pressable_button(200))
    {
        if (!sidebar.getGlobalBounds().contains(sf::Vector2f(*editor_details->mouse_pos_view)))
            if (!tex_selector->get_active())
                map->remove_tile(editor_details->mouse_pos_grid->x, editor_details->mouse_pos_grid->y, 0, tile_type);
    }
    // Toggle collision
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(editor_details->keybinds->at("TOGGLE_COLLISION"))) && pressable_button())
        tile_collision = tile_collision == true ? false : true;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(editor_details->keybinds->at("INCREASE_TYPE"))) && pressable_button())
        ++tile_type;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(editor_details->keybinds->at("DECREASE_TYPE"))) && pressable_button())
    {
        if (tile_type > 0)
            --tile_type;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(editor_details->keybinds->at("TOGGLE_TEX_SHEET"))) && pressable_button())
        tex_selector->get_hidden() == true ? tex_selector->set_hidden(false) : tex_selector->set_hidden(true);
}

void default_mode::update(const float &dt)
{
    update_input(dt);
    update_gui(dt);
}

void default_mode::render_gui(sf::RenderTarget &target)
{
    if (!tex_selector->get_active())
    {
        target.setView(*editor_details->view);
        target.draw(selector);
    }

    target.setView(state_details->window->getDefaultView());
    tex_selector->render(target);
    target.draw(sidebar);

    target.setView(*editor_details->view);
    target.draw(mouse_text);
}

void default_mode::render(sf::RenderTarget *target)
{
    render_gui(*target);
}

default_mode::~default_mode()
{
    delete tex_selector;
}