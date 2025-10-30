#pragma once
#include "Mob.h"

class Fantasma: public Mob
{


private:



public:

    Fantasma(const sf::Texture& textura);
    Fantasma(const sf::Texture& textura, sf::Vector2f posicionInicial);
    void fantasmaUpdate(sf::Vector2f& Posicionpersonaje);






};

