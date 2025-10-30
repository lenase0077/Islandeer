#include "Mob.h"
#include <cmath>
#include <iostream>



void Mob::perseguir(sf::Vector2f Posicionpersonaje, float aceleracion) {


    sf::Vector2f PosicionEnemigo = getPosition();

    sf::Vector2f Direccion = Posicionpersonaje - PosicionEnemigo;

    float longitud = std::sqrt(Direccion.x * Direccion.x + Direccion.y * Direccion.y);

    if (longitud > 1) {
        Direccion.x /= longitud;
        Direccion.y /= longitud;

        _velocidad.x = Direccion.x * aceleracion;
        _velocidad.y = Direccion.y * aceleracion;

    } else {
        _velocidad = {0, 0};
    }
}




void Mob::update() {

    updateColision();
}


void Mob::updateColision() {
    _colision.setColision(getGlobalBounds());

}




float Mob::getVida() const { return _vida; }

sf::Vector2f Mob::getVelocidad() {return _velocidad;}



void Mob::setVida(float vida) { _vida = vida; }
