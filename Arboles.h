#pragma once
#include "Estructura.h"
#include <cmath>


class Arbol : public Estructura {
public:

    Arbol(sf::Texture& texturaTronco, sf::Texture& texturaCopa, float x, float y, int idTronco, int idCopa);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void update(const sf::Vector2f& posicionJugador, const sf::Vector2f& posGlobalDelMouse, const sf::View& vista, const float& relacionAspecto, InventarioInterfaz& inventario, InventarioInterfaz& inventarioCofre, float deltatime) override;

private:
    sf::Sprite _spriteCopa;
    void setCopaFrame(int idFrame);



    // Variables para la animaci�n de viento
    float _tiempoAcumulado;
    float _velocidadViento;
};
