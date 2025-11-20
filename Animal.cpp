#include "Animal.h"
#include <iostream>
using namespace std;

Animal::Animal(const sf::Texture& textura)
{
    _colision.setID("Animal");
    setTexture(textura);
    setScale(0.8, 0.8);
    setTextureRect(sf::IntRect(0,0,32,32));
    setVida(100);

    _tiempoDivagar = (float)(rand() % (15 - 8 + 1) + 4) * 1000.0f;
    _tiempoEnReposo = (float)(rand() % (5 - 2 + 1) + 2) * 1000.0f;

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

Animal::Animal(const sf::Texture& textura, sf::Vector2f PosicionInicial)
{
    _colision.setID("Animal");
    setPosition(PosicionInicial);
    setTexture(textura);
    setTextureRect(sf::IntRect(0,0,32,32));
    setVida(100);

    _tiempoDivagar = clamp(rand(), 0, 100000);
    _tiempoEnReposo = clamp (rand (), 0, 5000);

    if (rand() % 2 == 0)
    {
        _estadoActual = EstadoAnimal::EsReposo;
        _frameActual = 1;
        _tiempoEnEstado = clamp(rand(), 0, (int)_tiempoEnReposo);
    }

    else
    {
        _estadoActual = EstadoAnimal::Divagando;
        _frameActual = 0;
        _tiempoEnEstado = clamp(rand(), 0, (int)_tiempoEnReposo);
    }
}


void Animal::enReposo (float deltaTime)
{
    setVelocidad({0.0f, 0.0f}); // Usamos setVelocidad

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

}

void Animal::recibirAtaqueDeEspada()
{
    _estadoActual = EstadoAnimal::Huyendo;
    _tiempoEnEstado = 0.f;
    _golpeadoPorEspada = true;

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

    setFrame(filaSpriteY, _frameActual);

}


void Animal::update(sf::Vector2f& Posicionpersonaje, float deltatime)
{
    updateColision();
    _tiempoEnEstado += deltatime;

    sf::Vector2f PosicionAnimal = getPosition();
    sf::Vector2f DireccionAlJugador = Posicionpersonaje - PosicionAnimal;
    float DistanciaJugador = std::sqrt(DireccionAlJugador.x * DireccionAlJugador.x + DireccionAlJugador.y * DireccionAlJugador.y);


    // --- LÓGICA DE DETECCIÓN Y CAMBIO DE ESTADO (PRIORIDAD) ---

    // 1. Detección por Proximidad
    if (DistanciaJugador < 60)
    {
        _estadoActual = EstadoAnimal::Huyendo;
        _tiempoEnEstado = 0.f;
    }
    // 2. Fin de Huida por Proximidad (solo si no fue golpeado)
    else if (_estadoActual == EstadoAnimal::Huyendo && DistanciaJugador > 100 && !_golpeadoPorEspada)
    {
        _estadoActual = EstadoAnimal::Divagando;
        _tiempoEnEstado = 0.f;
    }
    // 3. Fin de Huida por Golpe (tiempo fijo)
    else if (_estadoActual == EstadoAnimal::Huyendo && _golpeadoPorEspada && _tiempoEnEstado > 1000.f) // Huye por 1 segundos
    {
        _golpeadoPorEspada = false;
        _estadoActual = EstadoAnimal::Divagando;
        _tiempoEnEstado = 0.f;
    }

    // --- EJECUCION DEL ESTADO ACTUAL ---

    if (_estadoActual == EstadoAnimal::Huyendo)
    {
        huir(Posicionpersonaje, 1.5f);
        actualizarDireccion();
        actualizarSpriteAnimacion(deltatime);
    }
    else if (_estadoActual == EstadoAnimal::Divagando)
    {
        // divagar devuelve true si hay movimiento
        if (divagar(Posicionpersonaje, 0.5, deltatime))
        {
            actualizarDireccion();
            actualizarSpriteAnimacion(deltatime);

            // Lógica de probabilidad de entrar en reposo
            if (_tiempoEnEstado >= _tiempoDivagar)
            {
                if ((rand() % 100) == 0) // 1% de chance de entrar en reposo
                {
                    _estadoActual = EstadoAnimal::EsReposo;
                    _tiempoEnEstado = 0.f;
                    _frameActual = 1;
                }
            }
        }
        else {
            // Si divagar es llamado, pero la velocidad es 0, mostramos el frame estático
            setFrame(4, 0);
        }
    }
    else if (_estadoActual == EstadoAnimal::EsReposo)
    {
        enReposo(deltatime);

        // Volver a divagar después del tiempo de reposo
        if (_tiempoEnEstado >= _tiempoEnReposo)
        {
            _estadoActual = EstadoAnimal::Divagando;
            _tiempoEnEstado = 0.f;
            _frameActual = 0;
        }
    }

    // Finalmente, movemos el sprite
//    move(getVelocidad());
}

void Animal::actualizarDireccion()
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

void Animal::huir(sf::Vector2f& Posicionpersonaje, float aceleracion)
{
    // Vector: Animal - Personaje
    sf::Vector2f PosicionAnimal = getPosition();
    sf::Vector2f DireccionHuida = PosicionAnimal - Posicionpersonaje;

    float longitud = std::sqrt(DireccionHuida.x * DireccionHuida.x + DireccionHuida.y * DireccionHuida.y);

    if (longitud > 1.0f)
    {
        DireccionHuida.x /= longitud;
        DireccionHuida.y /= longitud;

        // Establecemos la velocidad de huida (usaremos aceleración 1.5f)
        setVelocidad({DireccionHuida.x * aceleracion, DireccionHuida.y * aceleracion});
    }
    else
    {
        // Si el jugador está tocando al animal, solo lo empujamos
        setVelocidad({aceleracion, 0.f});
    }
}

void Animal::recibirDanio()
{
    recibirAtaqueDeEspada();
}

