#pragma once
#include <SFML/Graphics.hpp>
#include "Comando.h"


enum class OpcionMenu {
    Ninguna,
    Jugar,
    Salir
};

class MenuPrincipal : public sf::Drawable {
private:
    sf::Texture _texturaLogo;
    sf::Texture _texturaBotonJugar;
    sf::Texture _texturaBotonSalir;

    sf::Sprite _spriteLogo;
    sf::Sprite _spriteBotonJugar;
    sf::Sprite _spriteBotonSalir;


public:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    MenuPrincipal();

    OpcionMenu actualizar(sf::Vector2f mousePos);


};
