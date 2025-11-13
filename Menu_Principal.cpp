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

    _spriteLogo.setOrigin(_spriteLogo.getLocalBounds().width / 2 , _spriteLogo.getLocalBounds().height / 2);
    _spriteBotonJugar.setOrigin(_spriteBotonJugar.getLocalBounds().width / 2 , _spriteBotonJugar.getLocalBounds().height / 2);
    _spriteBotonSalir.setOrigin(_spriteBotonSalir.getLocalBounds().width / 2 , _spriteBotonSalir.getLocalBounds().height / 2);

    // ---Posicionar Sprites (Centrados) ---
    // (Asumo una ventana de 1024x768)
    float centroVentanaX = 1024.f / 2.f;
    _spriteLogo.setScale(0.5,0.5);

    _spriteBotonJugar.setScale(1,1);
    _spriteBotonSalir.setScale(1,1);
    _spriteBackground.setScale(1,1);

    _spriteLogo.setPosition(centroVentanaX, 100 + _spriteLogo.getGlobalBounds().height / 2);

    _spriteBotonJugar.setPosition(centroVentanaX, 350 + _spriteBotonJugar.getGlobalBounds().height / 2);

    _spriteBotonSalir.setPosition(centroVentanaX, 480 + _spriteBotonJugar.getGlobalBounds().height / 2);

}

OpcionMenu MenuPrincipal::actualizar(sf::Vector2f mousePos)
{
    Comandos& input = Comandos::getInstancia();

    float const escalaObjetivoGrande = 1.1f;
    float const escalaObjetivoNormal = 1.0f;

    float const rotacionObjetivo = 5.0f;
    float const rotacionObjetivoNormal = 0.0f;

    float const suavizado = 0.1f;

    bool hoverJugar = clickEnPixel(mousePos, _spriteBotonJugar , _imagenJugar);
    bool hoverSalir = clickEnPixel(mousePos, _spriteBotonSalir , _imagenSalir);

    if (hoverJugar)
    {
        lerp(_escalaBotonJugar , escalaObjetivoGrande , suavizado);
        lerp (_rotacionBotonJugar , rotacionObjetivo , suavizado);
    }
    else
    {
        lerp(_escalaBotonJugar , escalaObjetivoNormal , suavizado);
        lerp (_rotacionBotonJugar , rotacionObjetivoNormal , suavizado);
    }

    if (hoverSalir)
    {
        lerp(_escalaBotonSalir , escalaObjetivoGrande , suavizado);
        lerp (_rotacionBotonSalir , rotacionObjetivo , suavizado);
    }
    else
    {
        lerp(_escalaBotonSalir , escalaObjetivoNormal , suavizado);
        lerp (_rotacionBotonSalir , rotacionObjetivoNormal , suavizado);
    }


    // --- 1. Efecto Hover (resaltado) ---
    _spriteBotonJugar.setScale(_escalaBotonJugar , _escalaBotonJugar);
    _spriteBotonJugar.setRotation(_rotacionBotonJugar);

    _spriteBotonSalir.setScale(_escalaBotonSalir , _escalaBotonSalir);
    _spriteBotonSalir.setRotation(_rotacionBotonSalir);

    if (input.mouseIzqRecienPresionado)
    {
        if (hoverJugar)
        {
            sonidoStardew.stop();
            return OpcionMenu::Jugar;
        }

        if (hoverSalir)
        {
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

     sf::Vector2f localPos = sprite.getInverseTransform().transformPoint(posClick);

     if (localPos.x < 0 || localPos.y < 0 || localPos.x >= image.getSize().x || localPos.y >= image.getSize().y)
     {
         return false;
     }


     sf::Color colorPixel = image.getPixel(static_cast<unsigned int>(localPos.x), static_cast<unsigned int>(localPos.y));

     return colorPixel.a > 10;

}

void MenuPrincipal::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(_spriteBackground, states);
    target.draw(_spriteLogo, states);
    target.draw(_spriteBotonJugar, states);
    target.draw(_spriteBotonSalir, states);
}

void MenuPrincipal::ajustarEscalaAutomaticamente(const sf::View& vista)
{
    const sf::Vector2f viewSize = vista.getSize();
    const sf::Vector2f viewCenter = vista.getCenter();
    const sf::Vector2f viewTopLeft = {viewCenter.x - viewSize.x / 2.f, viewCenter.y - viewSize.y / 2.f};

    const float ancho = 1024.f;
    const float alto = 769.f;

    float escalaX = viewSize.x / ancho;
    float escalaY = viewSize.y / alto;

    this -> setScale(escalaX , escalaY);
    this -> setPosition(viewTopLeft);
}
