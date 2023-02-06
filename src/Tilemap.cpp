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
        map[x][y][layer] = new tile(x, y, grid_sizef, tile_sheet, _rect);
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
    }
}

void tilemap::save_tilemap(const std::string save_file)
{
    std::ofstream ofs;
    ofs.open(save_file.c_str(), std::ios::trunc);
    if (!ofs.is_open())
        throw("ERROR::TILEMAP::COULDN'T SAVE TILEMAP TO FILE.\n");

    ofs << map_size.x << ' ' << map_size.y << '\n'
        << grid_sizeu << '\n'
        << layers << '\n'
        << this->texture_file << '\n';

    for (size_t x = 0; x < map_size.x; ++x)
        for (size_t y = 0; y < map_size.y; ++y)
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
    this->map_size.x = size.x;
    this->map_size.y = size.y;
    this->layers = layers;
    this->texture_file = texture;
    if (!tile_sheet.loadFromFile(this->texture_file))
        throw("ERROR::TILEMAP::FAILED TO LOAD FILE: " + texture_file + '\n');

    clear_map(); // Clear the old map
    map.reserve(this->map_size.x);
    for (size_t x = 0; x < this->map_size.x; ++x)
    {
        map.push_back(std::vector<std::vector<tile *>>());
        for (size_t y = 0; y < this->map_size.y; ++y)
        {
            // Allocate enough empty slots for the vector.
            map[x].reserve(this->map_size.y);
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
    for (size_t x = 0; x < map_size.x; ++x)
    {

        for (size_t y = 0; y < map_size.y; ++y)
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
