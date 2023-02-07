#include "../Headers/pch.h"
#include "../Headers/Tilemap.hpp"

tilemap::tilemap(float _grid_size, int width, int height, const std::string texture_file)
{
    init_textures();
    this->texture_file = texture_file;

    map_size_tiles.x = width;
    map_size_tiles.y = height;
    map_size_pixels.x = static_cast<float>(width) * _grid_size;
    map_size_pixels.y = static_cast<float>(height) * _grid_size;
    layers = 1;

    grid_sizef = _grid_size;
    grid_sizeu = static_cast<unsigned>(grid_sizef);

    collision_box.setSize(sf::Vector2f(_grid_size, _grid_size));
    collision_box.setFillColor(sf::Color(255, 0, 0, 80));
    collision_box.setOutlineColor(sf::Color::Red);
    collision_box.setOutlineThickness(-1.f);

    // Allocate enough empty slots for the map vector.
    map.reserve(map_size_tiles.x);

    for (size_t x = 0; x < map_size_tiles.x; ++x)
    {
        map.push_back(std::vector<std::vector<tile *>>());
        for (size_t y = 0; y < map_size_tiles.y; ++y)
        {
            // Allocate enough empty slots for the map vector.
            map[x].reserve(map_size_tiles.y);
            map[x].push_back(std::vector<tile *>());
            for (size_t z = 0; z < layers; ++z)
            {
                map[x][y].reserve(layers);
                map[x][y].push_back(nullptr);
            }
        }
    }

    /*Used for tile culling. */
    from_x = 0;
    to_x = 0;
    from_y = 0;
    to_y = 0;
    layer = 0;
}

void tilemap::init_textures()
{
    if (!tile_sheet.loadFromFile("../Assets/tiles/tilesheet1.png"))
        throw("ERROR::TILEMAP::FAILED TO LOAD FILE: " + texture_file + '\n');
}

void tilemap::update_collision(entity *entity, const float &dt)
{
    // Window collision
    update_worldborder_collision(entity);

    layer = 0;

    from_x = entity->get_gridpos(grid_sizeu).x - 1;
    if (from_x < 0)
        from_x = 0;

    to_x = entity->get_gridpos(grid_sizeu).x + 3;
    if (to_x >= map_size_tiles.x)
        to_x = map_size_tiles.x;

    from_y = entity->get_gridpos(grid_sizeu).y - 1;
    if (from_y < 0)
        from_y = 0;

    to_y = entity->get_gridpos(grid_sizeu).y + 3;
    if (to_y > map_size_tiles.y)
        to_y = map_size_tiles.y;

    // Todo: Refactor code ? :D
    for (int x = from_x; x < to_x; ++x)
    {
        for (int y = from_y; y < to_y; ++y)
        {
            sf::FloatRect next_pos = entity->get_next_pos(dt);
            if (map[x][y][layer]->get_collision() && map[x][y][layer]->intersects(next_pos))
            {
                sf::FloatRect player_bounds = entity->get_global_bounds();
                sf::FloatRect wall_bounds = map[x][y][layer]->get_global_bounds();
                /* Botton collision. */
                if (player_bounds.top < wall_bounds.top &&
                    player_bounds.top + player_bounds.height < wall_bounds.top + wall_bounds.width &&
                    player_bounds.left < wall_bounds.left + wall_bounds.width &&
                    player_bounds.left + player_bounds.width > wall_bounds.left)
                {
                    entity->reset_velocityY();
                    entity->set_pos(player_bounds.left, map[x][y][layer]->get_global_bounds().top - entity->get_global_bounds().height);
                }
                /* Top collision. */
                else if (player_bounds.top > wall_bounds.top &&
                         player_bounds.top + player_bounds.height > wall_bounds.top + wall_bounds.width &&
                         player_bounds.left < wall_bounds.left + wall_bounds.width &&
                         player_bounds.left + player_bounds.width > wall_bounds.left)
                {
                    entity->reset_velocityY();
                    entity->set_pos(player_bounds.left, map[x][y][layer]->get_global_bounds().top + entity->get_global_bounds().height);
                }
                /* Right collision. */
                if (player_bounds.left < wall_bounds.left &&
                    player_bounds.left + player_bounds.width < wall_bounds.left + wall_bounds.width &&
                    player_bounds.top < wall_bounds.top + wall_bounds.height &&
                    player_bounds.top + player_bounds.height > wall_bounds.top)
                {
                    entity->reset_velocityX();
                    entity->set_pos(wall_bounds.left - player_bounds.width, player_bounds.top);
                }
                /* Left collision. */
                else if (player_bounds.left > wall_bounds.left &&
                         player_bounds.left + player_bounds.width > wall_bounds.left + wall_bounds.width &&
                         player_bounds.top < wall_bounds.top + wall_bounds.height &&
                         player_bounds.top + player_bounds.height > wall_bounds.top)
                {
                    entity->reset_velocityX();
                    entity->set_pos(wall_bounds.left + wall_bounds.width, player_bounds.top);
                }
            }
        }
    }
}

void tilemap::update_worldborder_collision(entity *entity)
{
    if (entity->get_pos().x < 0.f)
    {
        entity->set_pos(0.f, entity->get_pos().y);
        entity->reset_velocityX();
    }
    else if (entity->get_pos().x + entity->get_global_bounds().width > map_size_pixels.x)
    {
        entity->set_pos(map_size_pixels.x - entity->get_global_bounds().width, entity->get_pos().y);
        entity->reset_velocityX();
    }

    if (entity->get_pos().y < 0.f)
    {
        entity->set_pos(entity->get_pos().x, 0.f);
        entity->reset_velocityY();
    }
    else if (entity->get_pos().y + entity->get_global_bounds().height > map_size_pixels.y)
    {
        entity->set_pos(entity->get_pos().x, map_size_pixels.y - entity->get_global_bounds().height);
        entity->reset_velocityY();
    }
}

void tilemap::update()
{
}

void tilemap::render(sf::RenderTarget &target, const entity *entity)
{
    for (auto &x : map)
        for (auto &y : x)
            for (auto &tile : y)
                if (tile != nullptr)
                {
                    tile->render(target);
                    if (tile->get_collision())
                    {
                        collision_box.setPosition(tile->get_pos()); // TODO remove later.
                        target.draw(collision_box);
                    }
                }
}

void tilemap::add_tile(const unsigned x, const unsigned y, const unsigned layer, const sf::IntRect &_rect, const bool collision, const short type)
{
    if (!(x < map_size_tiles.x && x >= 0 &&
          y < map_size_tiles.y && y >= 0 &&
          layer <= layers && layer >= 0))
        return; // Invalid bounds

    if (map[x][y][layer] == nullptr)
    {
        /* albe to add a new tile. */
        map[x][y][layer] = new tile(x, y, grid_sizef, tile_sheet, _rect, collision, type);
    }
}

void tilemap::remove_tile(const unsigned x, const unsigned y, const unsigned layer, const short type)
{
    if (!(x < map_size_tiles.x && x >= 0 &&
          y < map_size_tiles.y && y >= 0 &&
          layer <= layers && layer >= 0))
        return; // Invalid bounds
    if (map[x][y][layer] != nullptr && map[x][y][layer]->get_type() == type)
    {
        /* OK to add a new tile. */
        delete map[x][y][layer];
        map[x][y][layer] = nullptr;
    }
}

void tilemap::save_tilemap(const std::string save_file)
{
    std::ofstream ofs;
    ofs.open(save_file.c_str(), std::ios::trunc);
    if (!ofs.is_open())
        throw("ERROR::TILEMAP::COULDN'T SAVE TILEMAP TO FILE.\n");

    ofs << map_size_tiles.x << ' ' << map_size_tiles.y << '\n'
        << grid_sizeu << '\n'
        << layers << '\n'
        << this->texture_file << '\n';

    for (int x = 0; x < map_size_tiles.x; ++x)
        for (int y = 0; y < map_size_tiles.y; ++y)
            for (size_t z = 0; z < layers; ++z)
                if (map[x][y][z] != nullptr)
                    ofs << x << " " << y << " " << z << " " << map[x][y][z]->get_as_string() << " ";

    ofs.close();
}

void tilemap::load_tilemap(const std::string save_file)
{
    std::ifstream ifs;
    ifs.open(save_file.c_str(), std::ios::in);
    if (!ifs.is_open())
    {
        std::cout << ("ERROR::TILEMAP::COULDN'T LOAD TILEMAP FROM FILE.\n");
        return;
    }

    sf::Vector2u size;
    std::string texture;
    size_t grid_size = 0, layers = 0, x = 0, y = 0, z = 0;
    // Texture rect X and Y.
    size_t txrX = 0;
    size_t txrY = 0;
    bool collision = 0;
    short type = 0;
    ifs >> size.x >> size.y >> grid_size >> layers >> texture;

    this->grid_sizef = static_cast<float>(grid_size);
    this->grid_sizeu = grid_size;
    this->map_size_tiles.x = size.x;
    this->map_size_tiles.y = size.y;
    this->layers = layers;
    this->texture_file = texture;
    if (!tile_sheet.loadFromFile(this->texture_file))
        throw("ERROR::TILEMAP::FAILED TO LOAD FILE: " + texture_file + '\n');

    clear_map(); // Clear the old map
    map.reserve(this->map_size_tiles.x);
    for (int x = 0; x < this->map_size_tiles.x; ++x)
    {
        map.push_back(std::vector<std::vector<tile *>>());
        for (int y = 0; y < this->map_size_tiles.y; ++y)
        {
            // Allocate enough empty slots for the vector.
            map[x].reserve(this->map_size_tiles.y);
            map[x].push_back(std::vector<tile *>());
            for (size_t z = 0; z < this->layers; ++z)
            {
                map[x][y].reserve(this->layers);
                map[x][y].push_back(nullptr);
            }
        }
    }

    // Load all tiles
    while (ifs >> x >> y >> z >> txrX >> txrY >> collision >> type)
        map[x][y][z] = new tile(x, y, this->grid_sizef,
                                this->tile_sheet, sf::IntRect(txrX, txrY, grid_size, grid_size),
                                collision, type);

    ifs.close();
}

void tilemap::clear_map()
{
    for (int x = 0; x < map_size_tiles.x; ++x)
    {

        for (int y = 0; y < map_size_tiles.y; ++y)
        {

            for (size_t z = 0; z < layers; ++z)
            {
                delete map[x][y][z];
                map[x][y][z] = nullptr;
            }
            map[x][y].clear();
        }
    }
    map.clear();
}

const sf::Texture *tilemap::get_tilesheet() const
{
    return &tile_sheet;
}

tilemap::~tilemap()
{
    clear_map();
}
