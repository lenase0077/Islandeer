#pragma once
#include <SFML/Graphics.hpp>
#include "Comando.h"
#include <SFML/Audio.hpp>
#include "EstadodeJuego.h"




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
    sf::Texture _background;

    sf::Image _imagenLogo;
    sf::Image _imagenJugar;
    sf::Image _imagenSalir;

    sf::Sprite _spriteLogo;
    sf::Sprite _spriteBotonJugar;
    sf::Sprite _spriteBotonSalir;
    sf::Sprite _spriteBackground;

    sf::SoundBuffer bufferStardew;
    sf::Sound sonidoStardew;


public:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    MenuPrincipal();

    OpcionMenu actualizar(sf::Vector2f mousePos);

    bool clickEnPixel(sf::Vector2f posClick,  sf::Sprite& sprite, const sf::Image& imagen) const;


};
