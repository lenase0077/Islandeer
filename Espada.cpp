#include <iostream>
using namespace std;
#include "Espada.h"


Espada::Espada(){
        _textura.loadFromFile("espada.png");
        _sprite.setTexture(_textura);
//        _sprite.setOrigin(_textura.getSize().x / 2, _textura.getSize().y / 2);
        _sprite.setOrigin(3, 30);

        _sprite.scale(0.5,0.5);
    }

void Espada::update(const sf::Vector2f& mousePos, const sf::Vector2f& playerPos)
{
        sf::Vector2f dir = mousePos - playerPos;
        _angulo = std::atan2(dir.y, dir.x) * 180.f / 3.14159265f;
        _sprite.setRotation(_angulo);
        _sprite.setPosition(playerPos.x + 8, playerPos.y + 4); // o con un offset
}

void Espada::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(_sprite, states);
    }
