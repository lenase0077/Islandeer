#pragma once

#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>

class Cama : public sf::Transformable, public sf::Drawable
{
private:
    bool _construido = false;
    bool _dentroDeRango = false;
    const sf::Texture* _texturaCama;
    sf::Sprite _sprCama;
    void ajustarEscalaAutomaticamente(const sf::View& vista, const float& relacionAspecto);

public:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void update(const sf::Vector2f& posicionJugador);
    Cama(float posX, float posY, const sf::Texture& texturaCama);
    bool getDentroDeRango();
    void setConstruido(bool nuevoEstado);

};
