#include "Menu_Principal.h"
#include <iostream>







MenuPrincipal::MenuPrincipal()
{



    if (!_imagenLogo.loadFromFile("Logo.png")) {
        std::cout << "Error al cargar Logo.png" << std::endl;
    }
    if (!_imagenJugar.loadFromFile("Jugar.png")) {
        std::cout << "Error al cargar Jugar.png" << std::endl;
    }
    if (!_imagenSalir.loadFromFile("Salir.png")) {
        std::cout << "Error al cargar Salir.png" << std::endl;
    }

    if (!_background.loadFromFile("ImagenBackground.png")) {
        std::cout << "Error al cargar Salir.png" << std::endl;
    }


    if (!bufferStardew.loadFromFile("01.-Stardew-Valley-Overture.wav"))
    {
        return;
    }

    sonidoStardew.setBuffer(bufferStardew);
    sonidoStardew.play();
    sonidoStardew.setVolume(50.0);
//    sonido.setLoop(true);

    _texturaLogo.loadFromImage(_imagenLogo);
    _texturaBotonJugar.loadFromImage(_imagenJugar);
    _texturaBotonSalir.loadFromImage(_imagenSalir);

    _spriteLogo.setTexture(_texturaLogo);
    _spriteBotonJugar.setTexture(_texturaBotonJugar);
    _spriteBotonSalir.setTexture(_texturaBotonSalir);
    _spriteBackground.setTexture(_background);

    // ---Posicionar Sprites (Centrados) ---
    // (Asumo una ventana de 1024x768)
    float centroVentanaX = 1024.f / 2.f;

    _spriteLogo.setScale(0.5,0.5);
    _spriteBotonJugar.setScale(0.1,0.1);
    _spriteBotonSalir.setScale(0.1,0.1);
    _spriteBackground.setScale(0.9,0.9);

    _spriteLogo.setPosition(centroVentanaX - _spriteLogo.getGlobalBounds().width / 2, 100.f);


    _spriteBotonJugar.setPosition(centroVentanaX-192 - _spriteBotonJugar.getGlobalBounds().width / 2, 350.f);


    _spriteBotonSalir.setPosition(centroVentanaX-192 - _spriteBotonSalir.getGlobalBounds().width / 2, 480.f);


}


OpcionMenu MenuPrincipal::actualizar(sf::Vector2f mousePos)
{
    Comandos& input = Comandos::getInstancia();

    // --- 1. Efecto Hover (resaltado) ---
    _spriteBotonJugar.setScale(1.f, 1.f);
    _spriteBotonSalir.setScale(1.f, 1.f);

    if (clickEnPixel(mousePos,_spriteBotonJugar,_imagenJugar)) {
        _spriteBotonJugar.setScale(1.05f, 1.05f);
    }
    else if (clickEnPixel(mousePos,_spriteBotonSalir,_imagenSalir)) {
        _spriteBotonSalir.setScale(1.05f, 1.05f);
    }


    if (input.mouseIzqRecienPresionado)
    {
        if (clickEnPixel(mousePos,_spriteBotonJugar,_imagenJugar)) {
            sonidoStardew.stop();
            return OpcionMenu::Jugar;

        }

        if (clickEnPixel(mousePos,_spriteBotonSalir,_imagenSalir)) {
            return OpcionMenu::Salir;
        }
    }




    return OpcionMenu::Ninguna;
}


bool MenuPrincipal::clickEnPixel(sf::Vector2f posClick, sf::Sprite& sprite, const sf::Image& image) const
{

    if (!sprite.getGlobalBounds().contains(posClick))
    {
        return false;
    }

     sf::Vector2f localPos = posClick - sprite.getPosition();

     sf::Color colorPixel = image.getPixel(static_cast<unsigned int>(localPos.x), static_cast<unsigned int>(localPos.y));

     return colorPixel.a > 10;

}

void MenuPrincipal::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_spriteBackground, states);
    target.draw(_spriteLogo, states);
    target.draw(_spriteBotonJugar, states);
    target.draw(_spriteBotonSalir, states);
}
