#include "MesaDeCrafteo.h"
#include <cmath>

MesaDeCrafteo::MesaDeCrafteo(sf::Texture& texturaBloques, float posX, float posY, int id) :
    Estructura (texturaBloques,posX,posY,id){
}


void MesaDeCrafteo::update(const sf::Vector2f& posicionJugador, const sf::Vector2f& posGlobalDelMouse, const sf::Mouse& mouse, const sf::View& vista, const float& relacionAspecto, InventarioInterfaz& inventario){
    ///Detectar jugador cercano
    float distanciaJugador = sqrt(pow(posicionJugador.x - getPosition().x,2) + pow(posicionJugador.y - getPosition().y,2));

    if (distanciaJugador < 40){
        _sprite.setColor(sf::Color::Blue);
    }
    else _sprite.setColor(sf::Color::White);

    ///Adaptar UI a pantalla
    ///Mostrar UI
    ///Controlar selectores
    ///Verificar, quitar y dar items.
}
/*
void MesaDeCrafteo::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(_sprite, states);
}*/

