#include "Menu_Principal.h"
#include <iostream>

void MenuPrincipal::configurarTexto (sf::Text& texto, std::string nombre, int tamanio, float posX, float posY)
{
    texto.setFont(_fuente);
    texto.setString(nombre);
    texto.setCharacterSize(tamanio);
    texto.setFillColor(sf::Color::Yellow);
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
    if (!_imagenNuevaPartida.loadFromFile("Nueva partida.png")) {
        std::cout << "Error al cargar NuevaPartida.png" << std::endl;
    }
    if (!_imagenBotonCargar.loadFromFile("cargar_partida.png")) {
    std::cout << "Error al cargar CargarPartida.png" << std::endl;
    }

    if (!_imagenGuardar.loadFromFile("GuardarPartida.png")) {
        std::cout << "Error al cargar GuardarPartida.png" << std::endl;
    }
    if (!_imagenBotonMas.loadFromFile("botonMas.png"))
    {
        std::cout << "Falta imagen botonMas" << std::endl;
    }
    if (!_imagenBotonMenos.loadFromFile("botonMenos.png"))
    {
        std::cout << "Falta imagen botonMenos" << std::endl;
    }
    if (!_imagenBotonVolumen.loadFromFile("botonVolumen.png"))
    {
        std::cout << "Falta imagen botonVolumen" << std::endl;
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
    _texturaBotonNuevaPartida.loadFromImage(_imagenNuevaPartida);
    _texturaBotonJugar.loadFromImage(_imagenJugar);
    _texturaBotonOpciones.loadFromImage(_imagenOpciones);
    _texturaBotonSalir.loadFromImage(_imagenSalir);
    _texturaBotonVolumenGeneral.loadFromImage(_imagenVolumenGeneral);
    _texturaBotonVolver.loadFromImage(_imagenVolver);
    _texturaBotonCargar.loadFromImage(_imagenBotonCargar);
    _texturaBotonGuardar.loadFromImage(_imagenGuardar);
    _texturaBotonMas.loadFromImage(_imagenBotonMas);
    _texturaBotonMenos.loadFromImage(_imagenBotonMenos);
    _texturaTituloVolumen.loadFromImage(_imagenBotonVolumen);

    ///=====SPRITES=====

    _spriteLogo.setTexture(_texturaLogo);
    _spriteBotonNuevaPartida.setTexture(_texturaBotonNuevaPartida);
    _spriteBotonJugar.setTexture(_texturaBotonJugar);
    _spriteBotonOpciones.setTexture(_texturaBotonOpciones);
    _spriteBotonSalir.setTexture(_texturaBotonSalir);
    _spriteBotonVolumenGeneral.setTexture(_texturaBotonVolumenGeneral);
    _spriteBotonVolver.setTexture(_texturaBotonVolver);
    _spriteBotonGuardar.setTexture(_texturaBotonGuardar);
    _spriteBotonCargar.setTexture(_texturaBotonCargar);
    _spriteBackground.setTexture(_background);
    _spriteTituloVolumen.setTexture(_texturaTituloVolumen);
    _spriteBotonMas.setTexture(_texturaBotonMas);
    _spriteBotonMenos.setTexture(_texturaBotonMenos);

    ///======ORIGENES=====

    _spriteLogo.setOrigin(_spriteLogo.getLocalBounds().width / 2 , _spriteLogo.getLocalBounds().height / 2);
    _spriteBotonNuevaPartida.setOrigin(_spriteBotonNuevaPartida.getLocalBounds().width / 2 , _spriteBotonNuevaPartida.getLocalBounds().height / 2);
    _spriteBotonJugar.setOrigin(_spriteBotonJugar.getLocalBounds().width / 2 , _spriteBotonJugar.getLocalBounds().height / 2);
    _spriteBotonOpciones.setOrigin(_spriteBotonOpciones.getLocalBounds().width / 2 , _spriteBotonOpciones.getLocalBounds().height / 2);
    _spriteBotonSalir.setOrigin(_spriteBotonSalir.getLocalBounds().width / 2 , _spriteBotonSalir.getLocalBounds().height / 2);
    _spriteBotonVolumenGeneral.setOrigin(_spriteBotonVolumenGeneral.getLocalBounds().width / 2 , _spriteBotonVolumenGeneral.getLocalBounds().height / 2);
    _spriteBotonVolver.setOrigin(_spriteBotonVolver.getLocalBounds().width / 2 , _spriteBotonVolver.getLocalBounds().height / 2);
    _spriteBotonGuardar.setOrigin(_spriteBotonGuardar.getLocalBounds().width / 2 , _spriteBotonGuardar.getLocalBounds().height / 2);
    _spriteBotonCargar.setOrigin(_spriteBotonCargar.getLocalBounds().width / 2 , _spriteBotonCargar.getLocalBounds().height / 2);
    _spriteTituloVolumen.setOrigin(_spriteTituloVolumen.getLocalBounds().width / 2, _spriteTituloVolumen.getLocalBounds().height / 2);
    _spriteBotonMas.setOrigin(_spriteBotonMas.getLocalBounds().width / 2, _spriteBotonMas.getLocalBounds().height / 2);
    _spriteBotonMenos.setOrigin(_spriteBotonMenos.getLocalBounds().width / 2, _spriteBotonMenos.getLocalBounds().height / 2);


    // ---Posicionar Sprites (Centrados) ---
    // (Asumo una ventana de 1024x768)
    float centroVentanaX = 1024.f / 2.f;

    _spriteLogo.setScale(0.5f,0.5f);
    _spriteBotonNuevaPartida.setScale(1,1);
    _spriteBotonJugar.setScale(1,1);
    _spriteBotonOpciones.setScale(1,1);
    _spriteBotonSalir.setScale(1,1);
    _spriteBotonVolumenGeneral.setScale(1,1);
    _spriteBotonVolver.setScale(1,1);
    _spriteBotonGuardar.setScale(1,1);
    _spriteBotonCargar.setScale(1,1);
    _spriteBackground.setScale(1,1);
    _spriteTituloVolumen.setScale(1.0f, 1.0f);
    _spriteBotonMas.setScale(1,1);
    _spriteBotonMenos.setScale(1,1);

    ///======POSICIONES=====
    _spriteLogo.setPosition(centroVentanaX, 125);

    float inicioBotonesY = 315.0f;
    float separacion = 125.0f;

    _spriteBotonNuevaPartida.setPosition(centroVentanaX, inicioBotonesY);
    _spriteBotonJugar.setPosition(centroVentanaX, inicioBotonesY + separacion);
    _spriteBotonOpciones.setPosition(centroVentanaX, inicioBotonesY + (separacion*2));
    _spriteBotonSalir.setPosition(centroVentanaX, inicioBotonesY + (separacion*3));
    _spriteBotonVolumenGeneral.setPosition(centroVentanaX, inicioBotonesY);
    _spriteBotonGuardar.setPosition(centroVentanaX, inicioBotonesY + separacion);
    _spriteBotonCargar.setPosition(centroVentanaX, inicioBotonesY + (separacion*2));
    _spriteBotonVolver.setPosition(centroVentanaX, inicioBotonesY + (separacion*3));
    _spriteTituloVolumen.setPosition(centroVentanaX, 400);

    configurarTexto(_textoValorVolumen, "50", 50, centroVentanaX, 440);
    _spriteBotonMenos.setPosition(centroVentanaX - 100, 440);
    _spriteBotonMas.setPosition(centroVentanaX + 100, 440);

    if (!_fuente.loadFromFile("PIXEARG_.TTF")) {
        std::cout << "Error cargando fuente PIXEARG_.TTF" << std::endl;
    }
}

OpcionMenu MenuPrincipal::actualizar(sf::Vector2f mousePos)
{
    Comandos& input = Comandos::getInstancia();

    bool hoverNuevaPartida = clickEnPixel(mousePos, _spriteBotonNuevaPartida, _imagenNuevaPartida);
    bool hoverJugar = clickEnPixel(mousePos, _spriteBotonJugar , _imagenJugar);
    bool hoverOpciones = clickEnPixel(mousePos, _spriteBotonOpciones , _imagenOpciones);
    bool hoverSalir = clickEnPixel(mousePos, _spriteBotonSalir , _imagenSalir);
    bool hoverVolumenGeneral = clickEnPixel(mousePos, _spriteBotonVolumenGeneral , _imagenVolumenGeneral);
    bool hoverVolver = clickEnPixel(mousePos, _spriteBotonVolver , _imagenVolver);
    bool hoverGuardar = clickEnPixel(mousePos, _spriteBotonGuardar , _imagenGuardar);
    bool hoverCargar = clickEnPixel(mousePos, _spriteBotonCargar, _imagenBotonCargar);
    bool click = input.mouseIzqRecienPresionado;
    bool hoverMas = clickEnPixel(mousePos, _spriteBotonMas, _imagenBotonMas);
    bool hoverMenos = clickEnPixel(mousePos, _spriteBotonMenos, _imagenBotonMenos);

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

        if (hoverNuevaPartida)
        {
            lerp(_escalaBotonNuevaPartida , escalaObjetivoGrande , suavizado);
            lerp (_rotacionBotonNuevaPartida , rotacionObjetivo , suavizado);
        }
        else
        {
            lerp(_escalaBotonNuevaPartida , escalaObjetivoNormal , suavizado);
            lerp (_rotacionBotonNuevaPartida , rotacionObjetivoNormal , suavizado);
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

        if (hoverMenos)
        {
            lerp(_escalaBotonMenos, escalaObjetivoGrande, suavizado);
        }
        else
        {
            lerp(_escalaBotonMenos, escalaObjetivoNormal, suavizado);
        }
        _spriteBotonMenos.setScale(_escalaBotonMenos, _escalaBotonMenos);

        if (hoverMas)
        {
            lerp(_escalaBotonMas, escalaObjetivoGrande, suavizado);
        }
        else
        {
            lerp(_escalaBotonMas, escalaObjetivoNormal, suavizado);
        }
        _spriteBotonMas.setScale(_escalaBotonMas, _escalaBotonMas);

        // --- 1. Efecto Hover (resaltado) ---
        _spriteBotonJugar.setScale(_escalaBotonJugar , _escalaBotonJugar);
        _spriteBotonJugar.setRotation(_rotacionBotonJugar);

        _spriteBotonNuevaPartida.setScale(_escalaBotonNuevaPartida, _escalaBotonNuevaPartida);
        _spriteBotonNuevaPartida.setRotation(_rotacionBotonNuevaPartida);


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
            if (hoverNuevaPartida)
                return OpcionMenu::NuevaPartida;

            if (hoverOpciones)
            {
                _estadoMenu = EstadoMenu::SeleccionOpciones;
                return OpcionMenu::Opciones;
            }

            if (hoverSalir)
            {
                return OpcionMenu::Salir;
            }

            if (hoverCargar)
            {
                return OpcionMenu::Cargar;
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

        if (hoverGuardar)
        {
            lerp(_escalaBotonGuardar , escalaObjetivoGrande , suavizado);
            lerp (_rotacionBotonGuardar , rotacionObjetivo , suavizado);
        }

        else
        {
            lerp(_escalaBotonGuardar , escalaObjetivoNormal , suavizado);
            lerp (_rotacionBotonGuardar , rotacionObjetivoNormal , suavizado);
        }


        if (hoverCargar)
        {
            lerp(_escalaBotonCargar, escalaObjetivoGrande, suavizado);
            lerp(_rotacionBotonCargar, rotacionObjetivo, suavizado);
        }
        else
        {
            lerp(_escalaBotonCargar, escalaObjetivoNormal, suavizado);
            lerp(_rotacionBotonCargar, rotacionObjetivoNormal, suavizado);
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

        _spriteBotonGuardar.setScale(_escalaBotonGuardar, _escalaBotonGuardar);
        _spriteBotonGuardar.setRotation(_rotacionBotonGuardar);

        _spriteBotonCargar.setScale(_escalaBotonCargar, _escalaBotonCargar);
        _spriteBotonCargar.setRotation(_rotacionBotonCargar);

        if (click)
        {
            if (hoverVolumenGeneral)
            {
                _estadoMenu = EstadoMenu::ModificadorVolumen;
            }

            if (hoverGuardar)
            {
                return OpcionMenu::Guardar;
            }

            if (hoverCargar)
            {
                return OpcionMenu::Cargar;
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

        sf::FloatRect bounds = _textoValorVolumen.getLocalBounds();
        _textoValorVolumen.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);

        // Detectar Hover usando clickEnPixel
        bool hoverMas = clickEnPixel(mousePos, _spriteBotonMas, _imagenBotonMas);
        bool hoverMenos = clickEnPixel(mousePos, _spriteBotonMenos, _imagenBotonMenos);

        if (hoverMenos)
        {
            lerp(_escalaBotonMenos, escalaObjetivoGrande, suavizado);
        }
        else
        {
            lerp(_escalaBotonMenos, escalaObjetivoNormal, suavizado);
        }
        _spriteBotonMenos.setScale(_escalaBotonMenos, _escalaBotonMenos);


        if (hoverMas)
        {
            lerp(_escalaBotonMas, escalaObjetivoGrande, suavizado);
        }
        else
        {
            lerp(_escalaBotonMas, escalaObjetivoNormal, suavizado);
        }
        _spriteBotonMas.setScale(_escalaBotonMas, _escalaBotonMas);

        if (click)
        {
            if (hoverMenos)
            {
                _volumenGeneral -= 10.f;
                if (_volumenGeneral < 0) _volumenGeneral = 0;
                sonidoStardew.setVolume(_volumenGeneral);
            }

            if (hoverMas)
            {
                _volumenGeneral += 10.f;
                if (_volumenGeneral > 100) _volumenGeneral = 100;
                sonidoStardew.setVolume(_volumenGeneral);
            }

            if (hoverVolver)
            {
                _estadoMenu = EstadoMenu::SeleccionOpciones;
            }
        }

        // Animacion del boton volver
        if (hoverVolver) {
             lerp(_escalaBotonVolver , escalaObjetivoGrande , suavizado);
        } else {
             lerp(_escalaBotonVolver , escalaObjetivoNormal , suavizado);
        }
        _spriteBotonVolver.setScale(_escalaBotonVolver, _escalaBotonVolver);

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
        target.draw(_spriteBotonNuevaPartida, states);
        target.draw(_spriteBotonJugar, states);
        target.draw(_spriteBotonOpciones, states);
        target.draw(_spriteBotonSalir, states);
    }

    else if (_estadoMenu == EstadoMenu::SeleccionOpciones)
    {
        target.draw(_spriteBotonVolumenGeneral, states);
        target.draw(_spriteBotonGuardar, states);
        target.draw(_spriteBotonCargar, states);
        target.draw(_spriteBotonVolver, states);
    }

    else if (_estadoMenu == EstadoMenu::ModificadorVolumen)
    {
        target.draw(_spriteTituloVolumen , states);
        target.draw(_textoValorVolumen , states);
        target.draw(_spriteBotonMas , states);
        target.draw(_spriteBotonMenos , states);
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
