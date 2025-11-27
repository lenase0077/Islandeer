#include "Menu_Principal.h"
#include <iostream>

void MenuPrincipal::configurarTexto (sf::Text& texto, std::string nombre, int tamanio, float posX, float posY)
{
    texto.setFont(_fuente);
    texto.setString(nombre);
    texto.setCharacterSize(tamanio);
    texto.setFillColor(sf::Color::White);
    texto.setOutlineColor(sf::Color::Black);
    texto.setOutlineThickness(2);

    sf::FloatRect bounds = texto.getLocalBounds();
    texto.setOrigin(bounds.width / 2 , bounds.height / 2);

    texto.setPosition(posX , posY);
}

MenuPrincipal::MenuPrincipal()
{
    if (!_imagenLogo.loadFromFile("Logo.png")) {
        std::cout << "Error al cargar Logo.png" << std::endl;
    }
    if (!_imagenJugar.loadFromFile("Jugar.png")) {
        std::cout << "Error al cargar Jugar.png" << std::endl;
    }
    if (!_imagenOpciones.loadFromFile("Opciones.png")) {
        std::cout << "Error al cargar Opciones.png" << std::endl;
    }
    if (!_imagenSalir.loadFromFile("Salir.png")) {
        std::cout << "Error al cargar Salir.png" << std::endl;
    }
    if (!_background.loadFromFile("ImagenBackground.png")) {
        std::cout << "Error al cargar Salir.png" << std::endl;
    }
    if (!_imagenVolumenGeneral.loadFromFile("VolumenGneral.png")) {
        std::cout << "Error al cargar VolumenGneral.png" << std::endl;
    }
    if (!_imagenVolver.loadFromFile("Volver.png")) {
        std::cout << "Error al cargar Volver.png" << std::endl;
    }

    ///==========AUDIO===========

    if (bufferStardew.loadFromFile("01.-Stardew-Valley-Overture.wav"))
    {
        sonidoStardew.setBuffer(bufferStardew);
        sonidoStardew.setVolume(_volumenGeneral);
        sonidoStardew.play();
        sonidoStardew.setLoop(true);
    }

    ///======TEXTURAS======

    _texturaLogo.loadFromImage(_imagenLogo);
    _texturaBotonJugar.loadFromImage(_imagenJugar);
    _texturaBotonOpciones.loadFromImage(_imagenOpciones);
    _texturaBotonSalir.loadFromImage(_imagenSalir);
    _texturaBotonVolumenGeneral.loadFromImage(_imagenVolumenGeneral);
    _texturaBotonVolver.loadFromImage(_imagenVolver);

    ///=====SPRITES=====

    _spriteLogo.setTexture(_texturaLogo);
    _spriteBotonJugar.setTexture(_texturaBotonJugar);
    _spriteBotonOpciones.setTexture(_texturaBotonOpciones);
    _spriteBotonSalir.setTexture(_texturaBotonSalir);
    _spriteBotonVolumenGeneral.setTexture(_texturaBotonVolumenGeneral);
    _spriteBotonVolver.setTexture(_texturaBotonVolver);
    _spriteBackground.setTexture(_background);

    ///======ORIGENES=====

    _spriteLogo.setOrigin(_spriteLogo.getLocalBounds().width / 2 , _spriteLogo.getLocalBounds().height / 2);
    _spriteBotonJugar.setOrigin(_spriteBotonJugar.getLocalBounds().width / 2 , _spriteBotonJugar.getLocalBounds().height / 2);
    _spriteBotonOpciones.setOrigin(_spriteBotonOpciones.getLocalBounds().width / 2 , _spriteBotonOpciones.getLocalBounds().height / 2);
    _spriteBotonSalir.setOrigin(_spriteBotonSalir.getLocalBounds().width / 2 , _spriteBotonSalir.getLocalBounds().height / 2);
    _spriteBotonVolumenGeneral.setOrigin(_spriteBotonVolumenGeneral.getLocalBounds().width / 2 , _spriteBotonVolumenGeneral.getLocalBounds().height / 2);
    _spriteBotonVolver.setOrigin(_spriteBotonVolver.getLocalBounds().width / 2 , _spriteBotonVolver.getLocalBounds().height / 2);

    // ---Posicionar Sprites (Centrados) ---
    // (Asumo una ventana de 1024x768)
    float centroVentanaX = 1024.f / 2.f;
    _spriteLogo.setScale(0.5,0.5);

    _spriteBotonJugar.setScale(1,1);
    _spriteBotonOpciones.setScale(1,1);
    _spriteBotonSalir.setScale(1,1);
    _spriteBotonVolumenGeneral.setScale(1,1);
    _spriteBotonVolver.setScale(1,1);
    _spriteBackground.setScale(1,1);

    ///======POSICIONES=====
    _spriteLogo.setPosition(centroVentanaX, 100 + _spriteLogo.getGlobalBounds().height / 2);
    _spriteBotonJugar.setPosition(centroVentanaX, 420);
    _spriteBotonOpciones.setPosition(centroVentanaX, 560);
    _spriteBotonSalir.setPosition(centroVentanaX, 680);
    _spriteBotonVolumenGeneral.setPosition(centroVentanaX, 400);
    _spriteBotonVolver.setPosition(centroVentanaX, 650);

    if (!_fuente.loadFromFile("PIXEARG_.TTF")) {
        std::cout << "Error cargando fuente PIXEARG_.TTF" << std::endl;
    }

    configurarTexto(_textoTituloVolumen , "VOLUMEN MUSICA" , 40 , centroVentanaX , 400);
    configurarTexto(_botonMenos , "-" , 60 , centroVentanaX - 100 , 500);
    configurarTexto(_botonMas , "+" , 40 , centroVentanaX + 100, 500);
    configurarTexto(_textoValorVolumen , "50" , 50 , centroVentanaX , 500);
}

OpcionMenu MenuPrincipal::actualizar(sf::Vector2f mousePos)
{
    Comandos& input = Comandos::getInstancia();

    bool hoverJugar = clickEnPixel(mousePos, _spriteBotonJugar , _imagenJugar);
    bool hoverOpciones = clickEnPixel(mousePos, _spriteBotonOpciones , _imagenOpciones);
    bool hoverSalir = clickEnPixel(mousePos, _spriteBotonSalir , _imagenSalir);
    bool hoverVolumenGeneral = clickEnPixel(mousePos, _spriteBotonVolumenGeneral , _imagenVolumenGeneral);
    bool hoverVolver = clickEnPixel(mousePos, _spriteBotonVolver , _imagenVolver);
    bool click = input.mouseIzqRecienPresionado;

    float const escalaObjetivoGrande = 1.1f;
    float const escalaObjetivoNormal = 1.0f;
    float const rotacionObjetivo = 5.0f;
    float const rotacionObjetivoNormal = 0.0f;
    float const suavizado = 0.1f;

    if (_estadoMenu == EstadoMenu::Principal)
    {
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

        if (hoverOpciones)
        {
            lerp(_escalaBotonOpciones , escalaObjetivoGrande , suavizado);
            lerp (_rotacionBotonOpciones , rotacionObjetivo , suavizado);
        }
        else
        {
            lerp(_escalaBotonOpciones , escalaObjetivoNormal , suavizado);
            lerp (_rotacionBotonOpciones , rotacionObjetivoNormal , suavizado);
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

        _spriteBotonOpciones.setScale(_escalaBotonOpciones , _escalaBotonOpciones);
        _spriteBotonOpciones.setRotation(_rotacionBotonOpciones);

        _spriteBotonSalir.setScale(_escalaBotonSalir , _escalaBotonSalir);
        _spriteBotonSalir.setRotation(_rotacionBotonSalir);

        if (input.mouseIzqRecienPresionado)
        {
            if (hoverJugar)
            {
                return OpcionMenu::Jugar;
            }

            if (hoverOpciones)
            {
                _estadoMenu = EstadoMenu::SeleccionOpciones;
                return OpcionMenu::Opciones;
            }

            if (hoverSalir)
            {
                return OpcionMenu::Salir;
            }
        }
        if (click)
        {
            if (hoverJugar)
            {
                return OpcionMenu::Jugar;
            }
            if (hoverSalir)
            {
                return OpcionMenu::Salir;
            }

            if (hoverOpciones)
            {
                _estadoMenu = EstadoMenu::SeleccionOpciones;
                return OpcionMenu::Ninguna;
            }
        }
    }

    else if (_estadoMenu == EstadoMenu::SeleccionOpciones)
    {
        if (hoverVolumenGeneral)
        {
            lerp(_escalaBotonVolumenGeneral , escalaObjetivoGrande , suavizado);
            lerp (_rotacionBotonVolumenGeneral , rotacionObjetivo , suavizado);
        }
        else
        {
            lerp(_escalaBotonVolumenGeneral , escalaObjetivoNormal , suavizado);
            lerp (_rotacionBotonVolumenGeneral , rotacionObjetivoNormal , suavizado);
        }
        if (hoverVolver)
        {
            lerp(_escalaBotonVolver , escalaObjetivoGrande , suavizado);
            lerp (_rotacionBotonVolver , rotacionObjetivo , suavizado);
        }
        else
        {
            lerp(_escalaBotonVolver , escalaObjetivoNormal , suavizado);
            lerp (_rotacionBotonVolver , rotacionObjetivoNormal , suavizado);
        }

        _spriteBotonVolumenGeneral.setScale(_escalaBotonVolumenGeneral , _escalaBotonVolumenGeneral);
        _spriteBotonVolumenGeneral.setRotation(_rotacionBotonVolumenGeneral);

        _spriteBotonVolver.setScale(_escalaBotonVolver , _escalaBotonVolver);
        _spriteBotonVolver.setRotation(_rotacionBotonVolver);

        if (click)
        {
            if (hoverVolumenGeneral)
            {
                _estadoMenu = EstadoMenu::ModificadorVolumen;
            }
            if (hoverVolver)
            {
                _estadoMenu = EstadoMenu::Principal;
            }
        }
    }

    else if (_estadoMenu == EstadoMenu::ModificadorVolumen)
    {
        _textoValorVolumen.setString(std::to_string((int)_volumenGeneral));
        sf::Color colorHover = sf::Color::Yellow;
        sf::Color colorNormal = sf::Color::White;

        ///BOTON MENOS
        if (_botonMenos.getGlobalBounds().contains(mousePos))
        {
            _botonMenos.setFillColor(colorHover);
            if (click)
            {
                _volumenGeneral -= 10.f;
                if (_volumenGeneral < 0)
                {
                    _volumenGeneral = 0;
                }
                sonidoStardew.setVolume(_volumenGeneral);
            }
        }
        else
        {
            _botonMenos.setFillColor(colorNormal);
        }

        ///BOTON MAS
        if (_botonMas.getGlobalBounds().contains(mousePos))
        {
            _botonMas.setFillColor(colorHover);
            if (click)
            {
                _volumenGeneral += 10.f;
                if (_volumenGeneral > 100)
                {
                    _volumenGeneral = 100;
                }
                sonidoStardew.setVolume(_volumenGeneral);
            }
        }
        else
        {
            _botonMas.setFillColor(colorNormal);
        }

        ///BOTON VOLVER
        if (click && hoverVolver)
        {
            _estadoMenu = EstadoMenu::SeleccionOpciones;
        }

        return OpcionMenu::Ninguna;
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

    if (_estadoMenu == EstadoMenu::Principal)
    {
        target.draw(_spriteBotonJugar, states);
        target.draw(_spriteBotonOpciones, states);
        target.draw(_spriteBotonSalir, states);
    }

    else if (_estadoMenu == EstadoMenu::SeleccionOpciones)
    {
        target.draw(_spriteBotonVolumenGeneral, states);
        target.draw(_spriteBotonVolver, states);
    }

    else if (_estadoMenu == EstadoMenu::ModificadorVolumen)
    {
        target.draw(_textoTituloVolumen , states);
        target.draw(_textoValorVolumen , states);
        target.draw(_botonMas , states);
        target.draw(_botonMenos , states);
        target.draw(_spriteBotonVolver, states);
    }
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

float MenuPrincipal::getVolumen ()
{
    return _volumenGeneral;
}

void MenuPrincipal::iniciarMusica()
{
    if (sonidoStardew.getStatus() != sf::Sound::Playing)
    {
        sonidoStardew.play();
    }
}

void MenuPrincipal::detenerMusica()
{
    sonidoStardew.stop();
}
