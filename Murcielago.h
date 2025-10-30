#pragma once
#include "Mob.h"

class Murcielago : public Mob
{
    private:
        int _frameActual = 2;
        float _tiempoAnimacion;

    public:
        Murcielago(const sf::Texture& textura);
        Murcielago(const sf::Texture& textura , sf::Vector2f PosicionInicial);
        void murcielagoUpdate(sf::Vector2f& Posicionpersonaje , float deltaTime);
        void Animar(float deltaTime);
};


