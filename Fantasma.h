#pragma once
#include "Mob.h"

class Fantasma: public Mob
{

public:

    Fantasma(const sf::Texture& textura);
    Fantasma(const sf::Texture& textura , sf::Vector2f PosicionInicial);
    void fantasmaUpdate(sf::Vector2f& Posicionpersonaje);
};

