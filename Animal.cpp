#include "Animal.h"
#include <iostream>
using namespace std;

Animal::Animal(const sf::Texture& textura)
{
    _colision.setID("Animal");
    setTexture(textura);
    setScale(0.8 , 0.8);
    setTextureRect(sf::IntRect(0,0,32,32));
    setVida(100);
}

Animal::Animal(const sf::Texture& textura , sf::Vector2f PosicionInicial)
{
    _colision.setID("Animal");
    setPosition(PosicionInicial);
    setTexture(textura);
    setTextureRect(sf::IntRect(0,0,32,32));
    setVida(100);
}

void Animal::AnimalUpdate(sf::Vector2f& Posicionpersonaje, float deltatime)
{
    updateColision();

    if (divagar(Posicionpersonaje , 0.5 , deltatime))
    {
        if (abs(getVelocidad().x) > abs(getVelocidad().y))
        {
            if (getVelocidad().x > 0)
            {
                _direccionActual = DireccionMob::Derecha;
            }
            else
            {
                _direccionActual = DireccionMob::Izquierda;

            }
        }

        else
        {
            if (getVelocidad().y > 0)
            {
                _direccionActual = DireccionMob::Abajo;
            }
            else
            {
                _direccionActual = DireccionMob::Arriba;
            }
        }
    }

    move(getVelocidad());
    actualizarSpriteAnimacion(deltatime);
}

void Animal::actualizarSpriteAnimacion (float deltaTime)
{
    _tiempoDeAnimar += deltaTime;

    if (_tiempoDeAnimar >= 250)
    {
        _frameActual++;
        if (_frameActual >= 4)
        {
            _frameActual = 0;
        }
        _tiempoDeAnimar -= 250;
    }

    int filaSpriteY = 0;

    switch(_direccionActual)
    {
    case DireccionMob::Abajo:
        filaSpriteY = 0;
        break;
    case DireccionMob::Izquierda:
        filaSpriteY = 1;
        break;
    case DireccionMob::Arriba:
        filaSpriteY = 2;
        break;
    case DireccionMob::Derecha:
        filaSpriteY = 3;
        break;
    }

    setFrame(filaSpriteY , _frameActual);

}


void Animal::update(sf::Vector2f& Posicionpersonaje, float deltatime)
{
    AnimalUpdate(Posicionpersonaje, deltatime);
}
