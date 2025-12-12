#pragma once
#include "Particula.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

class SistemaParticulas {

private:
    std::vector<Particula> _particulas;
    sf::CircleShape _forma;

public:
    SistemaParticulas();
    void emitirVeneno(sf::Vector2f posOrigen);
    void update(float dt);
    void draw(sf::RenderWindow& window);
    void emitirBrilloDorado(sf::Vector2f posOrigen);

};
