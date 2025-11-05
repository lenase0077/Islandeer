#pragma once
#include <SFML/Graphics.hpp>
#include "Mob.h"

class Animal : public Mob
{
    public:
        Animal(const sf::Texture& textura);
        Animal(const sf::Texture& textura , sf::Vector2f PosicionInicial);
        void update(sf::Vector2f& Posicionpersonaje, float deltatime);
        void AnimalUpdate(sf::Vector2f& Posicionpersonaje, float deltatime);
        void actualizarSpriteAnimacion (float deltaTime);

    private:
        int _frameActual = 0;
        float _tiempoDeAnimar;
};
