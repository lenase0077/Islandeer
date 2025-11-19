#pragma once
#include <SFML/Graphics.hpp>
#include "Comando.h"
#include <SFML/Audio.hpp>
#include "EstadodeJuego.h"
#include "funcionesInterpolacion.h"
#include <string>

enum class OpcionMenu {
    Ninguna,
    Jugar,
    Opciones,
    Salir
};

enum class EstadoMenu{
    Principal,
    SeleccionOpciones,
    ModificadorVolumen
};

class MenuPrincipal : public sf::Drawable, public sf::Transformable{
private:
    EstadoMenu _estadoMenu = EstadoMenu::Principal;
    sf::Texture _texturaLogo;
    sf::Texture _texturaBotonJugar;
    sf::Texture _texturaBotonOpciones;
    sf::Texture _texturaBotonSalir;
    sf::Texture _texturaBotonVolumenGeneral;
    sf::Texture _texturaBotonVolver;
    sf::Texture _background;

    sf::Image _imagenLogo;
    sf::Image _imagenJugar;
    sf::Image _imagenOpciones;
    sf::Image _imagenSalir;
    sf::Image _imagenVolumenGeneral;
    sf::Image _imagenVolver;

    sf::Sprite _spriteLogo;
    sf::Sprite _spriteBotonJugar;
    sf::Sprite _spriteBotonOpciones;
    sf::Sprite _spriteBotonSalir;
    sf::Sprite _spriteBotonVolumenGeneral;
    sf::Sprite _spriteBotonVolver;
    sf::Sprite _spriteBackground;

    sf::SoundBuffer bufferStardew;
    sf::Sound sonidoStardew;
    float _volumenGeneral = 50.0f;

    float _escalaBotonJugar = 1.0f;
    float _escalaBotonOpciones = 1.0f;
    float _escalaBotonSalir = 1.0f;
    float _escalaBotonVolumenGeneral = 1.0f;
    float _escalaBotonVolver = 1.0f;

    float _rotacionBotonJugar = 0.0f;
    float _rotacionBotonOpciones = 0.0f;
    float _rotacionBotonSalir = 0.0f;
    float _rotacionBotonVolumenGeneral = 0.0f;
    float _rotacionBotonVolver = 0.0f;

    sf::Font _fuente;
    sf::Text _textoTituloVolumen;
    sf::Text _textoValorVolumen;
    sf::Text _botonMenos;
    sf::Text _botonMas;

public:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    MenuPrincipal();
    OpcionMenu actualizar(sf::Vector2f mousePos);
    bool clickEnPixel(sf::Vector2f posClick,  sf::Sprite& sprite, const sf::Image& imagen) const;
    void ajustarEscalaAutomaticamente(const sf::View& vista);
    float getVolumen ();
    void configurarTexto (sf::Text& texto, std::string nombre, int tamanio, float posX, float posY);
};
