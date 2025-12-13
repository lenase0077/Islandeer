#include "BarcoHuida.h"


bool BarcoHuida::eligioIrse(){
    return _eligioIrse;
}

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
    float distanciaJugador = sqrt(pow((posicionJugador.x) - (getPosition().x + 16) ,2) + pow((posicionJugador.y) - (getPosition().y + 16),2));

    if (distanciaJugador < 30){
        _dentroDeRango = true;
        _sprBarco.setColor(sf::Color::Red);
    }
    else{
        _dentroDeRango = false;
        _sprBarco.setColor(sf::Color::White);
    }
}

bool BarcoHuida::getDentroDeRango(){
    return _dentroDeRango;
}
