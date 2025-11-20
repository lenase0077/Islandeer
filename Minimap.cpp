#include "Minimap.h"
#include <iostream> // Para mensajes de error

Minimap::Minimap(sf::Vector2f displaySize, sf::Vector2f screenPosition)
{
    _position = screenPosition;
    _displaySize = displaySize;
    _sprite.setPosition(_position);

    _playerIcon.setRadius(3.f);
    _playerIcon.setFillColor(sf::Color::White); // Rojo resalta mejor sobre verde/azul
    _playerIcon.setOrigin(3.f, 3.f);

    _scale = 1.f;
    _mapWidthInTiles = 0;
    _mapHeightInTiles = 0;
    _tilePixelSize = 32; // Escala por defecto
}

void Minimap::build(const TileMap& map)
{
    _mapWidthInTiles = map.getMapWidth();
    _mapHeightInTiles = map.getMapHeight();
    _tilePixelSize = map.getTileWidth();

    sf::Image minimapImage;
    minimapImage.create(_mapWidthInTiles, _mapHeightInTiles, sf::Color::Black);

    for (int y = 0; y < _mapHeightInTiles; ++y)
    {
        for (int x = 0; x < _mapWidthInTiles; ++x)
        {
            int id = map.getTileID(x, y);

            sf::Color color = getColorForID(id);

            minimapImage.setPixel(x, y, color);
        }
    }

    if (!_texture.loadFromImage(minimapImage)) {
        std::cout << "Error cargando textura del minimapa" << std::endl;
    }

    _texture.setSmooth(false);
    _sprite.setTexture(_texture);

    float scaleX = _displaySize.x / (float)_mapWidthInTiles;
    float scaleY = _displaySize.y / (float)_mapHeightInTiles;


    _scale = std::min(scaleX, scaleY);

    _sprite.setScale(_scale, _scale);
}

void Minimap::update(sf::Vector2f playerPosition)
{

    float gridX = playerPosition.x / _tilePixelSize;
    float gridY = playerPosition.y / _tilePixelSize;

    _playerMapPos.x = gridX * _scale;
    _playerMapPos.y = gridY * _scale;
}


sf::Color Minimap::getColorForID(int id) const
{

    // CASO AGUA
    if (id == 93 || id == 94 || id == 95  || id == 96
         || id == 102 || id == 103 || id == 104
          || id == 109 || id == 110 || id == 111 || id == 112) return sf::Color(0, 105, 148);

    // CASO AGUA CLARA
    if (id == 22 || id == 23 || id == 24
        || id == 30 || id == 31 || id == 32
        || id == 38 || id == 39 || id == 40) return sf::Color(142, 199, 232);

    // CASO PASTO
    if (id == 28 || id == 29 || id == 36 || id == 37) {
        return sf::Color(34, 139, 34);
    }

    // CASO ARENA
    if (id <= 68 ||id == 69 || id == 70 || id == 71 ||
        id == 77 || id == 78 || id == 79 ||id == 80 ||id == 85 ||
        id == 86|| id == 87|| id == 88 || id == 89 ) return sf::Color(238, 214, 175);

    // DEFAULT (desconocido)
    return sf::Color(139, 69, 19); // Saddle Brown
}

void Minimap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);

    sf::CircleShape playerIcon = _playerIcon;
    playerIcon.setPosition(_position + _playerMapPos);

    target.draw(playerIcon, states);

}
