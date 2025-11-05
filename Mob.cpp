#include "Mob.h"
#include <iostream>

bool Mob::perseguir(sf::Vector2f Posicionpersonaje, float aceleracion) {

    sf::Vector2f PosicionEnemigo = getPosition();

    sf::Vector2f Direccion = Posicionpersonaje - PosicionEnemigo;

    float longitud = std::sqrt(Direccion.x * Direccion.x + Direccion.y * Direccion.y);

    if (longitud < 100 && longitud > 1) {
        Direccion.x /= longitud;
        Direccion.y /= longitud;

        _velocidad.x = Direccion.x * aceleracion;
        _velocidad.y = Direccion.y * aceleracion;

        return true;
    }
    return false;
}

bool Mob::divagar(sf::Vector2f Posicionpersonaje, float aceleracion, float deltaTime)
{

    sf::Vector2f PosicionEnemigo = getPosition();
    sf::Vector2f Direccion = Posicionpersonaje - PosicionEnemigo;

    sf::Vector2f DireccionAObjetivo = _posicionObjetivoDivagar - PosicionEnemigo;
    float DistanciaAObjetivo = std::sqrt(DireccionAObjetivo.x * DireccionAObjetivo.x + DireccionAObjetivo.y * DireccionAObjetivo.y);

    _tiempoDivagar += deltaTime;

    if (_tiempoDivagar > 3000.0f || DistanciaAObjetivo <= 5.0f) {
        float PosX = (rand() % 101) - 50.f;
        float PosY = (rand() % 101) - 50.f;

        _posicionObjetivoDivagar.x = PosicionEnemigo.x + PosX;
        _posicionObjetivoDivagar.y = PosicionEnemigo.y + PosY;

        _tiempoDivagar = 0.0f;
    }

    sf::Vector2f DireccionDivagar = _posicionObjetivoDivagar - PosicionEnemigo;
    float longitudDivagar = std::sqrt(DireccionDivagar.x * DireccionDivagar.x + DireccionDivagar.y * DireccionDivagar.y);

    if (longitudDivagar > 1.0f) {
        DireccionDivagar.x /= longitudDivagar;
        DireccionDivagar.y /= longitudDivagar;

        _velocidad.x = DireccionDivagar.x * (aceleracion * 0.5f);
        _velocidad.y = DireccionDivagar.y * (aceleracion * 0.5f);
    } else {
        _velocidad = {0.f, 0.f};
    }
    return true;
}

void Mob::update(sf::Vector2f& Posicionpersonaje, float deltatime)
{

}

void Mob::updateColision() {
    _colision.setColision(getGlobalBounds());

}

void Mob::setFrame(int fila, int columna) {
    setTextureRect((sf::IntRect(columna * 32, fila * 32, 32, 32)));
}

float Mob::getVida() const {
    return _vida;
}

sf::Vector2f Mob::getVelocidad() {
    return _velocidad;
}


void Mob::setVida(float vida) {
    _vida = vida;
}
