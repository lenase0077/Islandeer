#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "json.hpp"
#include "Colisionador.h"
using json = nlohmann::json;


class TileMap : public sf::Drawable, public sf::Transformable {
private:

    sf::VertexArray _verticesSuelo;
    sf::VertexArray _verticesObjetos;
    sf::Texture _texturaSuelo;
    sf::Texture _texturaObjetos;

    int _tileWidth, _tileHeight;
    int _width, _height;


public:

    std::vector<Colisionador> _colisiones;

    bool loadFromJSON(const std::string& filename,
                      const std::string& tilesetSuelo,
                      const std::string& tilesetObjetos);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        states.transform *= getTransform();
        states.texture = &_texturaSuelo;
        target.draw(_verticesSuelo, states);
        states.texture = &_texturaObjetos;
        target.draw(_verticesObjetos, states);
    }
};
