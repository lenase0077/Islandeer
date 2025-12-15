#include "Mob.h"
#include <iostream>

Mob::Mob() :
    _velocidad({0.f, 0.f}),
    _vida(100.f),
    _tiempoDivagar(0),
    _posicionObjetivoDivagar({0.f, 0.f}),
    _fuerzaRetroceso({0.f, 0.f}),
    _tiempoDeAnimar(0.f),
    _frameActual(0),
    _direccionActual(DireccionMob::Abajo)
{
}

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

    if (_tiempoDivagar > 10000.0f || DistanciaAObjetivo <= 5.0f) {

        float rango = 400.0f;

        float PosX = (float)(rand() % (int)rango) - (rango / 2.0f);
        float PosY = (float)(rand() % (int)rango) - (rango / 2.0f);

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

sf::FloatRect Mob::getColisionBounds() const
{
    return getTransform().transformRect(getLocalBounds());
}

void Mob::chocar (Colisionador& colision)
{
    sf::FloatRect rectanguloColision = getColisionBounds();
    rectanguloColision.left += _velocidad.x;
    rectanguloColision.top += _velocidad.y;

    if (rectanguloColision.intersects(colision.getColision()))
    {
        _velocidad = {0.f , 0.f};
    }

}


void Mob::update(sf::Vector2f& Posicionpersonaje, float deltatime)
{
    if (std::abs(_fuerzaRetroceso.x) > 0.1f || std::abs(_fuerzaRetroceso.y) > 0.1f)
    {
        move(_fuerzaRetroceso);


        _fuerzaRetroceso *= 0.90f;
    }
    else
    {
        _fuerzaRetroceso = {0.f, 0.f};
    }

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

sf::Vector2f Mob::setVelocidad(sf::Vector2f velocidad) {
    _velocidad = velocidad;
}


void Mob::setVida(float vida) {
    _vida = vida;
}

void Mob::bajarVida(float danio)
{
    _vida -= danio;
    recibirDanio();

    if (_vida < 0)
    {
        _vida = 0;
    }
}

void Mob::empujar(sf::Vector2f fuerza)
{
    _fuerzaRetroceso = fuerza;
}


