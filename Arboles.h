#pragma once
#include "Estructura.h"
#include <cmath>


class Arbol : public Estructura {
public:

    Arbol(sf::Texture& texturaTronco, sf::Texture& texturaCopa, float x, float y, int idTronco, int idCopa);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void update(const sf::Vector2f& posJugador, const sf::Vector2f& posMouse, const sf::Mouse& mouse, const sf::View& vista, const float& relacionAspecto, InventarioInterfaz& inventario, float deltatime)  override;

private:
    sf::Sprite _spriteCopa;
    void setCopaFrame(int idFrame);



    // Variables para la animación de viento
    float _tiempoAcumulado;
    float _velocidadViento;
};
