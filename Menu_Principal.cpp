#include "Menu_Principal.h"
#include <iostream>

MenuPrincipal::MenuPrincipal()
{

    if (!_texturaLogo.loadFromFile("Logo.png")) {
        std::cout << "Error al cargar Logo.png" << std::endl;
    }
    if (!_texturaBotonJugar.loadFromFile("Jugar.png")) {
        std::cout << "Error al cargar Jugar.png" << std::endl;
    }
    if (!_texturaBotonSalir.loadFromFile("Salir.png")) {
        std::cout << "Error al cargar Salir.png" << std::endl;
    }

    _spriteLogo.setTexture(_texturaLogo);
    _spriteBotonJugar.setTexture(_texturaBotonJugar);
    _spriteBotonSalir.setTexture(_texturaBotonSalir);

    // ---Posicionar Sprites (Centrados) ---
    // (Asumo una ventana de 1024x768)
    float centroVentanaX = 1024.f / 2.f;

    _spriteLogo.setScale(0.4,0.4);
    _spriteBotonJugar.setScale(0.1,0.1);
    _spriteBotonSalir.setScale(0.1,0.1);

    _spriteLogo.setPosition(centroVentanaX - _spriteLogo.getGlobalBounds().width / 2, 100.f);


    _spriteBotonJugar.setPosition(centroVentanaX-150 - _spriteBotonJugar.getGlobalBounds().width / 2, 350.f);


    _spriteBotonSalir.setPosition(centroVentanaX-150 - _spriteBotonSalir.getGlobalBounds().width / 2, 480.f);


}


OpcionMenu MenuPrincipal::actualizar(sf::Vector2f mousePos)
{
    Comandos& input = Comandos::getInstancia();

    // --- 1. Efecto Hover (resaltado) ---
    _spriteBotonJugar.setScale(1.f, 1.f);
    _spriteBotonSalir.setScale(1.f, 1.f);

    if (_spriteBotonJugar.getGlobalBounds().contains(mousePos)) {
        _spriteBotonJugar.setScale(1.05f, 1.05f);
    }
    else if (_spriteBotonSalir.getGlobalBounds().contains(mousePos)) {
        _spriteBotonSalir.setScale(1.05f, 1.05f);
    }


    if (input.mouseIzqRecienPresionado)
    {
        if (_spriteBotonJugar.getGlobalBounds().contains(mousePos)) {
            return OpcionMenu::Jugar;
        }

        if (_spriteBotonSalir.getGlobalBounds().contains(mousePos)) {
            return OpcionMenu::Salir;
        }
    }

    return OpcionMenu::Ninguna;
}

void MenuPrincipal::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_spriteLogo, states);
    target.draw(_spriteBotonJugar, states);
    target.draw(_spriteBotonSalir, states);
}
