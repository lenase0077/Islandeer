#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

class Espada : public sf::Drawable {
private:
    sf::Sprite _sprite;
    sf::Texture _textura;
    float _angulo;

public:
    Espada();
    void update(const sf::Vector2f& mousePos, const sf::Vector2f& playerPos);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};
