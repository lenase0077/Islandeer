#include <iostream>
using namespace std;
#include "Raton.h"

void Raton::update(const sf::RenderWindow& window) {
        _posicion = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    }

sf::Vector2f Raton::getPosicion() const
{ return _posicion; }
