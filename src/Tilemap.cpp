#include "../Headers/pch.h"
#include "../Headers/Tilemap.hpp"

tilemap::tilemap(float _grid_size, unsigned width, unsigned height, const std::string texture_file)
{
    init_textures();
    this->texture_file = texture_file;

    map_size.x = width;
    map_size.y = height;
    layers = 1;

    grid_sizef = _grid_size;
    grid_sizeu = static_cast<unsigned>(grid_sizef);

    // Allocate enough empty slots for the vector.
    map.reserve(map_size.x);

    for (size_t x = 0; x < map_size.x; ++x)
    {
        map.push_back(std::vector<std::vector<tile *>>());
        for (size_t y = 0; y < map_size.y; ++y)
        {
            // Allocate enough empty slots for the vector.
            map[x].reserve(map_size.y);
            map[x].push_back(std::vector<tile *>());
            for (size_t z = 0; z < layers; ++z)
            {
                map[x][y].reserve(layers);
                map[x][y].push_back(nullptr);
            }
        }
    }
}

void tilemap::init_textures()
{
    if (!tile_sheet.loadFromFile("../Assets/tiles/tilesheet1.png"))
        throw("ERROR::TILEMAP::FAILED TO LOAD FILE: " + texture_file + '\n');
}

void tilemap::update() {}

void tilemap::render(sf::RenderTarget &target)
{
    for (auto &x : map)
        for (auto &y : x)
            for (auto &tile : y)
                if (tile != nullptr)
                    tile->render(target);
}

void tilemap::add_tile(const unsigned x, const unsigned y, const unsigned layer, const sf::IntRect &_rect)
{
    if (!(x < map_size.x && x >= 0 &&
          y < map_size.y && y >= 0 &&
          layer <= layers && layer >= 0))
        return; // Invalid bounds

    if (map[x][y][layer] == nullptr)
    {
        /* OK to add a new tile. */
        map[x][y][layer] = new tile(x * grid_sizef, y * grid_sizef, grid_sizef, tile_sheet, _rect);
        std::cout << "New tile at " << x << ' ' << y << '\n';
    }
}

void tilemap::remove_tile(const unsigned x, const unsigned y, const unsigned layer)
{
    if (!(x < map_size.x && x >= 0 &&
          y < map_size.y && y >= 0 &&
          layer <= layers && layer >= 0))
        return; // Invalid bounds
    if (map[x][y][layer] != nullptr)
    {
        /* OK to add a new tile. */
        delete map[x][y][layer];
        map[x][y][layer] = nullptr;
        std::cout << "Deleted tile at " << x << ' ' << y << '\n';
    }
}

void tilemap::save_tilemap(const std::string file_name)
{
    std::ofstream ofs;
    ofs.open(file_name.c_str());
    if (!ofs.is_open())
        throw("ERROR::TILEMAP::COULDN'T SAVE TILEMAP TO FILE.\n");

    ofs << map_size.x << ' ' << map_size.y << '\n'
        << grid_sizeu << '\n'
        << layers << '\n'
        << texture_file << '\n';

    for (size_t x = 0; x < map_size.x; ++x)
    {
        for (size_t y = 0; y < map_size.y; ++y)
        {
            for (size_t z = 0; z < layers; ++z)
            {
                ofs << 1 << 1 << 2 << 3 << 5 << ' ';
                // ofs << map[x][y][z];
            }
        }
        ofs << '\n';
    }

    ofs.close();
}

void tilemap::load_tilemap(const std::string file_name) {}

const sf::Texture *tilemap::get_tilesheet() const
{
    return &tile_sheet;
}

tilemap::~tilemap()
{
    for (size_t x = 0; x < map_size.x; ++x)
        for (size_t y = 0; y < map_size.y; ++y)
            for (size_t z = 0; z < layers; ++z)
                delete map[x][y][z];
}
