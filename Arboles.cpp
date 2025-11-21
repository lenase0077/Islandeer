#include "Arboles.h"

Arbol::Arbol(sf::Texture& texturaTronco, sf::Texture& texturaCopa, float x, float y, int idTronco, int idCopa)
    : Estructura(texturaTronco, x, y, idTronco)
{
    _spriteCopa.setTexture(texturaCopa);

    int anchoCopa = 32;
    int altoCopa = 64;

    int coordX = idCopa * anchoCopa;
    int coordY = 0;

    _spriteCopa.setTextureRect(sf::IntRect(coordX, coordY, anchoCopa, altoCopa));

    _spriteCopa.setOrigin(anchoCopa / 2.0f, altoCopa - 10.0f);

    _spriteCopa.setPosition(16.f, 0.f);

    _tiempoAcumulado = (rand() % 100) / 10.0f;
    _velocidadViento = 1.5f;
}

void Arbol::update(const sf::Vector2f& posJugador, const sf::Vector2f& posMouse, const sf::Mouse& mouse, const sf::View& vista, const float& relacionAspecto, InventarioInterfaz& inventario)
{
    Estructura::update(posJugador, posMouse, mouse, vista, relacionAspecto, inventario);

    float dt = 1.0f / 60.0f;
    _tiempoAcumulado += dt * _velocidadViento;

    float angulo = std::sin(_tiempoAcumulado) * 3.0f;
    _spriteCopa.setRotation(angulo);
}

void Arbol::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    Estructura::draw(target, states);

    states.transform *= getTransform();

    target.draw(_spriteCopa, states);
}
