#pragma once
#include "SFML/Graphics.hpp"
#include "Colisionador.h"
#include <string>


class Mob: public sf::Sprite
{
private:



        sf::Vector2f _velocidad;
        float _vida;


public:



        Colisionador _colision;

        sf::Vector2f getVelocidad();

        bool perseguir(sf::Vector2f Posicionpersonaje, float aceleracion);


        float getVida() const;
        void setVida(float vida);


        void update();
        void updateColision();

        void setFrame(int fila , int columna);




};

