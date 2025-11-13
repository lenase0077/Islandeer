#pragma once
#include "SFML/Graphics.hpp"
#include "Colisionador.h"
#include <string>
#include <cmath>
#include <ctime>

enum class DireccionMob {
    Arriba,
    Abajo,
    Izquierda,
    Derecha
};

class Mob: public sf::Sprite
{
private:
        float _vida;
        sf::Vector2f _posicionObjetivoDivagar;
        sf::Vector2f _velocidad;

public:
        Mob();
        void chocar (Colisionador& colision);
        sf::FloatRect getColisionBounds() const;
        DireccionMob _direccionActual;
        Colisionador _colision;
        sf::Vector2f getVelocidad();
        sf::Vector2f setVelocidad(sf::Vector2f velocidad);
        bool perseguir(sf::Vector2f Posicionpersonaje, float aceleracion);
        bool divagar(sf::Vector2f Posicionpersonaje, float aceleracion, float deltaTime);
        float getVida() const;
        void setVida(float vida);
        virtual void update(sf::Vector2f& Posicionpersonaje, float deltatime);
        void updateColision();
        void setFrame(int fila , int columna);
        sf::Clock& getRelojMob();
        int _frameActual;
        float _tiempoDivagar;
        float _tiempoDeAnimar;

};

