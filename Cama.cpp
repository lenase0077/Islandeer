#include "Cama.h"

Cama::Cama(float posX, float posY, const sf::Texture& texturaCama){
    setPosition(posX,posY);

    _texturaCama = &texturaCama;
    _sprCama.setTexture(texturaCama);
}

void Cama::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    states.transform *= getTransform();
    target.draw(_sprCama, states);
}

void Cama::update(const sf::Vector2f& posicionJugador){
    ///Detectar jugador cercano
    float distanciaJugador = sqrt(pow((posicionJugador.x) - (getPosition().x + 16) ,2) + pow((posicionJugador.y) - (getPosition().y + 16),2));

    if (distanciaJugador < 30){
        _dentroDeRango = true;
    }
    else{
        _dentroDeRango = false;
    }

    if (_construido){
        _sprCama.setColor(sf::Color::White);
    }
    else{
        _sprCama.setColor(sf::Color(255,255,255,50));
    }
}

bool Cama::getDentroDeRango(){
    return _dentroDeRango;
}

void Cama::setConstruido(bool nuevoEstado){
    _construido = nuevoEstado;
}
