#pragma once
#include <SFML/Graphics.hpp>

class Raton {
private:
    sf::Vector2f _posicion;
public:
    void update(const sf::RenderWindow& window);
    sf::Vector2f getPosicion() const;


};
