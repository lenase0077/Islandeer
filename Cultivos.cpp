#include <iostream>
#include "Cultivos.h"
using namespace std;

cultivo::cultivo(sf::Texture& textura, float x, float y, int filaSprite, int idProducto, int idSemilla)
{
    setPosition(x, y);
    _sprite.setTexture(textura);
    _idProducto = idProducto;
    _idSemilla = idSemilla;
    _faseDeCrecimiento = 0;
    _tiempoAcumulado = 0;
    _tiempoParaCrecer = 5.0f;
    _listoParaCosechar = false;
    _tipoCultivo = filaSprite;

    _sprite.setTextureRect(sf::IntRect(0, filaSprite*32, 32, 32));
}

void cultivo::update (float deltaTime)
{
    if (_faseDeCrecimiento < 2)
    {
        _tiempoAcumulado += deltaTime / 1000.0;

        if (_tiempoAcumulado >= _tiempoParaCrecer)
        {
            _faseDeCrecimiento++;
            _tiempoAcumulado = 0;
            int left = _faseDeCrecimiento * 32;
            int top = _tipoCultivo * 48;
            _sprite.setTextureRect(sf::IntRect(left,top,32,48));

            if (_faseDeCrecimiento == 2) _listoParaCosechar = true;

        }
    }
}

bool cultivo::intentarCosechar (std::list<Loot>& listaLoots, FabricaItems& fabrica)
{
    sf::Vector2f pos = getPosition();
    pos.x += 16;
    pos.y += 16;
    float rx, ry;

    if (_listoParaCosechar)
    {
        // 1. Tira el producto que le configuramos al nacer
        rx = (rand() % 20) - 10; ry = (rand() % 20) - 10;
        listaLoots.emplace_back(fabrica, sf::Vector2f(pos.x + rx, pos.y + ry), _idProducto, rand() % 2 + 1);

        // 2. Tira la semilla
        rx = (rand() % 20) - 10; ry = (rand() % 20) - 10;
        listaLoots.emplace_back(fabrica, sf::Vector2f(pos.x + rx, pos.y + ry), _idSemilla, rand() % 2 + 1);

        // 3. Chance extra
        if (rand() % 100 < 40) {
            rx = (rand() % 20) - 10; ry = (rand() % 20) - 10;
            listaLoots.emplace_back(fabrica, sf::Vector2f(pos.x + rx, pos.y + ry), _idProducto, rand() % 2 + 1);
        }
    }
    else
    {
        // Solo devuelve semilla
        rx = (rand() % 20) - 10; ry = (rand() % 20) - 10;
        listaLoots.emplace_back(fabrica, sf::Vector2f(pos.x + rx, pos.y + ry), _idSemilla, rand() % 2 + 1);
    }

    return true;
}


void cultivo::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(_sprite, states);
}

sf::FloatRect cultivo::getBounds() const {
    return getTransform().transformRect(_sprite.getGlobalBounds());
}

bool cultivo::estaMaduro() const {
    return _listoParaCosechar;
}
