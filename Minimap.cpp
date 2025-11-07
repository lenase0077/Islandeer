#include "Minimap.h"
#include <iostream> // Para mensajes de error

Minimap::Minimap(sf::Vector2f displaySize, sf::Vector2f screenPosition)
{
    _position = screenPosition;

    _displaySize = displaySize;

    _sprite.setPosition(_position);


    _playerIcon.setRadius(3.f); // Radio de 3 píxeles
    _playerIcon.setFillColor(sf::Color::White);
    _playerIcon.setOrigin(3.f, 3.f); // Centramos el círculo para que la posición sea el centro



    // Inicializamos las variables de tamaño y escala
    _worldWidth = 0.f;
    _worldHeight = 0.f;
    _scale = 1.f; // Escala por defecto
}

void Minimap::build(const TileMap& map)
{
    _worldWidth = map.getMapWidth() * map.getTileWidth();
    _worldHeight = map.getMapHeight() * map.getTileHeight();

    if (!_texture.create(_worldWidth, _worldHeight)) {
        std::cout << "Error al crear la RenderTexture del minimapa" << std::endl;
        return;
    }

    _texture.clear(sf::Color::Transparent);
    _texture.draw(map);
    _texture.display();
    _texture.setSmooth(false);


    _sprite.setTexture(_texture.getTexture());


    _scale = _displaySize.x / _worldWidth;

    _sprite.setScale(_scale, _scale);
}

void Minimap::update(sf::Vector2f playerPosition)
{

    _playerMapPos = playerPosition * _scale;

}

void Minimap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);

    sf::CircleShape playerIcon = _playerIcon;
    playerIcon.setPosition(_position + _playerMapPos);
    target.draw(playerIcon, states);

}
