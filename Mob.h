#pragma once
#include "SFML/Graphics.hpp"
#include "Colisionador.h"
#include <string>
#include <cmath>

enum class DireccionMob {
    Arriba,
    Abajo,
    Izquierda,
    Derecha
};

class Mob: public sf::Sprite
{
private:
        sf::Vector2f _velocidad;
        float _vida;
        float _tiempoDivagar;
        sf::Vector2f _posicionObjetivoDivagar;

public:
        Mob();
        DireccionMob _direccionActual;
        Colisionador _colision;
        sf::Vector2f getVelocidad();
        bool perseguir(sf::Vector2f Posicionpersonaje, float aceleracion);
        bool divagar(sf::Vector2f Posicionpersonaje, float aceleracion, float deltaTime);
        float getVida() const;
        void setVida(float vida);
        virtual void update(sf::Vector2f& Posicionpersonaje, float deltatime);
        void updateColision();
        void setFrame(int fila , int columna);
        sf::Clock& getRelojMob();
        int _frameActual;
        float _tiempoDeAnimar;
};

