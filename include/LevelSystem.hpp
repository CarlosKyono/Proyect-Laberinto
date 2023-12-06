#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <SFMLExtensions.hpp>

class LevelSystem
{
public:
    enum class TILE
    {
        EMPTY,
        START,
        END,
        WALL,
        ENEMY,
        WAYPOINT
    };

    static void loadLevelFile(const std::string &path, float tileSize = 100.f);
    static void render(sf::RenderWindow &window);
    static sf::Color getColor(TILE t);
    static void setColor(TILE t, sf::Color c);
    static TILE getTile(sf::Vector2u pos);
    static sf::Vector2f getTilePosition(sf::Vector2u pos);
    static TILE getTileAt(sf::Vector2f pos);

private:
    static const sf::Vector2f DEFAULT_OFFSET;
    static const float DEFAULT_TILE_SIZE;

    static std::unique_ptr<TILE[]> _tiles;
    static size_t _width;
    static size_t _height;
    static sf::Vector2f _offset;
    static float _tileSize;
    static std::map<TILE, sf::Color> _colours;
    static std::vector<std::unique_ptr<sf::RectangleShape>> _sprites;

    static void buildSprites();
};

#include "LevelSystem.hpp"

const sf::Vector2f LevelSystem::DEFAULT_OFFSET(0.0f, 30.0f);
const float LevelSystem::DEFAULT_TILE_SIZE = 100.f;

std::unique_ptr<LevelSystem::TILE[]> LevelSystem::_tiles;
size_t LevelSystem::_width;
size_t LevelSystem::_height;
sf::Vector2f LevelSystem::_offset = DEFAULT_OFFSET;

float LevelSystem::_tileSize = DEFAULT_TILE_SIZE;
std::vector<std::unique_ptr<sf::RectangleShape>> LevelSystem::_sprites;

std::map<LevelSystem::TILE, sf::Color> LevelSystem::_colours{
    {LevelSystem::TILE::WALL, sf::Color::White},
    {LevelSystem::TILE::END, sf::Color::Red}};

sf::Color LevelSystem::getColor(LevelSystem::TILE t)
{
    auto it = _colours.find(t);
    if (it == _colours.end())
    {
        _colours[t] = sf::Color::Transparent;
    }
    return _colours[t];
}

void LevelSystem::setColor(LevelSystem::TILE t, sf::Color c)
{
    _colours[t] = c;
}

void LevelSystem::loadLevelFile(const std::string &path, float tileSize)
{
    _tileSize = tileSize;
    size_t w = 0, h = 0;
    std::string buffer;

    std::ifstream f(path);
    if (f.good())
    {
        f.seekg(0, std::ios::end);
        buffer.resize(f.tellg());
        f.seekg(0);
        f.read(&buffer[0], buffer.size());
        f.close();
    }
    else
    {
        throw std::invalid_argument("Couldn't open level file: " + path);
    }

    std::vector<TILE> temp_tiles;
    for (size_t i = 0; i < buffer.size(); ++i)
    {
        const char c = buffer[i];
        switch (c)
        {
        case 'w':
            temp_tiles.push_back(TILE::WALL);
            break;
        case 's':
            temp_tiles.push_back(TILE::START);
            break;
        case 'e':
            temp_tiles.push_back(TILE::END);
            break;
        case ' ':
            temp_tiles.push_back(TILE::EMPTY);
            break;
        case '+':
            temp_tiles.push_back(TILE::WAYPOINT);
            break;
        case 'n':
            temp_tiles.push_back(TILE::ENEMY);
            break;
        case '\n':
            if (w == 0)
            {
                w = i;
            }
            h++;
            break;
        default:
            std::cout << c << std::endl;
        }
    }

    if (temp_tiles.size() != (w * h))
    {
        throw std::invalid_argument("Can't parse level file: " + path);
    }
    _tiles = std::make_unique<TILE[]>(w * h);
    _width = w;
    _height = h;
    std::copy(temp_tiles.begin(), temp_tiles.end(), &_tiles[0]);
    std::cout << "Level " << path << " Loaded. " << w << "x" << h << std::endl;

    std::cout << "Level size: " << _width << "x" << _height << std::endl;

    buildSprites();
}

void LevelSystem::buildSprites()
{
    _sprites.clear();
    for (size_t y = 0; y < _height; ++y)
    {
        for (size_t x = 0; x < _width; ++x)
        {
            _sprites.emplace_back(std::make_unique<sf::RectangleShape>());
            auto &s = _sprites.back();
            s->setPosition(getTilePosition({x, y}));
            s->setSize(sf::Vector2f(_tileSize, _tileSize));
            s->setFillColor(getColor(getTile({x, y})));
        }
    }
}

sf::Vector2f LevelSystem::getTilePosition(sf::Vector2u pos)
{
    return sf::Vector2f(pos.x, pos.y) * _tileSize;
}

LevelSystem::TILE LevelSystem::getTile(sf::Vector2u pos)
{
    if (pos.x >= _width || pos.y >= _height)
    {
        throw std::out_of_range("Tile out of range: (" + std::to_string(pos.x) + "," + std::to_string(pos.y) + ")");
    }
    return _tiles[(pos.y * _width) + pos.x];
}

LevelSystem::TILE LevelSystem::getTileAt(sf::Vector2f pos)
{
    auto a = pos - _offset;
    if (a.x < 0 || a.y < 0)
    {
        throw std::out_of_range("Tile out of range ");
    }
    return getTile(sf::Vector2u((pos - _offset) / (_tileSize)));
}

void LevelSystem::render(sf::RenderWindow &window)
{
    for (size_t i = 0; i < _width * _height; ++i)
    {
        window.draw(*_sprites[i]);
    }
}
