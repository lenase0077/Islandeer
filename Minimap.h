#pragma once
#include <SFML/Graphics.hpp>
#include "TileMap.h"
#include "Mob.h"
#include <list>
#include <memory>

class Minimap : public sf::Drawable
{
public:
    Minimap(sf::Vector2f displaySize, sf::Vector2f screenPosition);

    void build(const TileMap& map);

    void update(sf::Vector2f playerPosition);
    void empujar(sf::Vector2f fuerza);

protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:

    sf::Color getColorForID(int id) const;


    sf::Texture _texture;
    sf::Sprite        _sprite;
    sf::CircleShape   _playerIcon;

    sf::Vector2f      _position;
    sf::Vector2f _displaySize;
    float             _scale;
    sf::Vector2f _fuerzaRetroceso;




    int               _mapWidthInTiles;
    int               _mapHeightInTiles;
    int               _tilePixelSize;

    sf::Vector2f _playerMapPos;
};
