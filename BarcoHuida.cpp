#include "BarcoHuida.h"

BarcoHuida::BarcoHuida(float posX, float posY, const sf::Texture& texturaBarco){
    setPosition(posX,posY);

    _texturaBarco = &texturaBarco;
    _sprBarco.setTexture(texturaBarco);
}

void BarcoHuida::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    states.transform *= getTransform();
    target.draw(_sprBarco, states);
}

void BarcoHuida::update(const sf::Vector2f& posicionJugador){
    ///Detectar jugador cercano
    float distanciaJugador = sqrt(pow((posicionJugador.x) - (getPosition().x + 79) ,2) + pow((posicionJugador.y) - (getPosition().y + 64),2));

    if (distanciaJugador < 64){
        _dentroDeRango = true;
    }
    else{
        _dentroDeRango = false;
    }

    if (_construido){
        _sprBarco.setColor(sf::Color::White);
    }
    else{
        _sprBarco.setColor(sf::Color(255,255,255,50));
    }
}

bool BarcoHuida::getDentroDeRango(){
    return _dentroDeRango;
}

void BarcoHuida::setConstruido(bool nuevoEstado){
    _construido = nuevoEstado;
}
