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

    _tiempoDivagar = clamp(rand() , 0, 5000);
    _tiempoEnReposo = clamp (rand () , 0 , 5000);

    if (rand() % 2 == 0)
    {
        _estadoActual = EstadoAnimal::EsReposo;
        _frameActual = 0;
        _tiempoEnEstado = clamp(rand() , 0 , (int)_tiempoEnReposo);
    }

    else
    {
        _estadoActual = EstadoAnimal::Divagando;
        _frameActual = 0;
        _tiempoEnEstado = clamp(rand() , 0 , (int)_tiempoEnReposo);
    }
}

Animal::Animal(const sf::Texture& textura , sf::Vector2f PosicionInicial)
{
    _colision.setID("Animal");
    setPosition(PosicionInicial);
    setTexture(textura);
    setTextureRect(sf::IntRect(0,0,32,32));
    setVida(100);

    _tiempoDivagar = clamp(rand() , 0, 100000);
    _tiempoEnReposo = clamp (rand () , 0 , 50000);

    if (rand() % 2 == 0)
    {
        _estadoActual = EstadoAnimal::EsReposo;
        _frameActual = 1;
        _tiempoEnEstado = clamp(rand() , 0 , (int)_tiempoEnReposo);
    }

    else
    {
        _estadoActual = EstadoAnimal::Divagando;
        _frameActual = 0;
        _tiempoEnEstado = clamp(rand() , 0 , (int)_tiempoEnReposo);
    }
}


void Animal::enReposo (float deltaTime)
{
    getVelocidad() = {0.0f , 0.0f};

    _tiempoDeAnimar += deltaTime;

    if (_tiempoDeAnimar >= 5000)
    {
        if (_frameActual == 0)
        {
            _frameActual = 1;
        }
        else
        {
            _frameActual = 0;
        }

        _tiempoDeAnimar -= 5000;

    }

    setFrame(4, _frameActual);

    if (_tiempoEnEstado >= _tiempoEnReposo)
    {
        _estadoActual = EstadoAnimal::Divagando;
        _tiempoEnEstado = 0.f;
        _frameActual = 0;
    }
}

void Animal::AnimalUpdate(sf::Vector2f& Posicionpersonaje, float deltatime)
{
    updateColision();
    _tiempoEnEstado += deltatime;

    if (_estadoActual == EstadoAnimal::Divagando)
    {
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

            if (_tiempoEnEstado >= _tiempoDivagar)
            {
                _estadoActual = EstadoAnimal::EsReposo;
                _tiempoEnEstado = 0.f;
                _frameActual = 1;
            }

            actualizarSpriteAnimacion(deltatime);

        }

        move(getVelocidad());
    }

    else if (_estadoActual == EstadoAnimal::EsReposo)
    {
        enReposo(deltatime);
    }
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
