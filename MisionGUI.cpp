#include "MisionGUI.h"
#include "funcionesInterpolacion.h"
#include "Funciones.h"

MisionGUI::MisionGUI(const sf::Font& fuenteTextos, const sf::Texture& texturaMision, const std::string& titulo, const std::string& explicacion, const int& recompensa)
{
    _recompensa = recompensa;

    _fuentesTextos = &fuenteTextos;

    _textoTitulo.setFont(*_fuentesTextos);
    _textoTitulo.setString(titulo);
    _textoTitulo.setCharacterSize(8);
    _textoTitulo.setScale(1.2,1.2);
    _textoTitulo.setPosition(7,4);
    _textoTitulo.setColor(sf::Color::White);
    _textoTitulo.setOutlineColor(sf::Color::Black);
    _textoTitulo.setOutlineThickness(1);

    _textoExplicacion.setFont(*_fuentesTextos);
    _textoExplicacion.setString( AjustarStringAutomaticamente(explicacion, 8*0.8, 240));
    _textoExplicacion.setCharacterSize(8);
    _textoExplicacion.setScale(0.8,0.8);
    _textoExplicacion.setPosition(10,18);
    _textoExplicacion.setColor(sf::Color::White);

    _textoMonedas.setFont(*_fuentesTextos);
    _textoMonedas.setCharacterSize(8);
    _textoMonedas.setString("$" + std::to_string(_recompensa));
    _textoMonedas.setColor(sf::Color::Black);

    _sprFondo.setTexture( texturaMision);
    _sprFondo.setTextureRect({0,0, 256, 64});

    _sprBotonReclamar.setTexture( texturaMision);
    _sprBotonReclamar.setTextureRect({256,0, 64, 16});
    _sprBotonReclamar.setPosition(214,47);
    _sprBotonReclamar.setOrigin(32,8);

}

void MisionGUI::setOculto(bool nuevoEstado)
{
    _oculto = nuevoEstado;
}
bool MisionGUI::getOculto()
{
    return _oculto;
}
bool MisionGUI::getCompletado()
{
    return _completado;
}

void MisionGUI::update(const sf::Vector2f& posGlobalDelMouse)
{
    if (_botonReclamar.estaDentro(posGlobalDelMouse.x, posGlobalDelMouse.y, true)){
        ///Seleccion suave
        sf::Vector2f escalaActualBoton = _sprBotonReclamar.getScale();
        lerp(escalaActualBoton, {1.1,1.1},0.2);
        _sprBotonReclamar.setScale(escalaActualBoton);

    }
    else{
        ///deseleccion suave
        sf::Vector2f escalaActualBoton = _sprBotonReclamar.getScale();
        lerp(escalaActualBoton, {1,1},0.2);
        _sprBotonReclamar.setScale(escalaActualBoton);
    }
}

void MisionGUI::ajustarEscalaAutomaticamente(const sf::View& vista, const float& relacionAspecto)
{
    // Escala proporcional al tamanio de la vista
    sf::Vector2f escalaCartel(sf::Vector2f(vista.getSize().x/512, vista.getSize().y/512 * relacionAspecto));

    float centroX = ((_sprFondo.getGlobalBounds().width/ 2)) * escalaCartel.x;

    // Calcula posiciones

    sf::Vector2f posicionCartel;

    if(!_oculto) posicionCartel = sf::Vector2f(vista.getCenter().x - centroX, vista.getCenter().y- vista.getSize().y/2.5);
    else posicionCartel = sf::Vector2f(vista.getCenter().x - centroX, vista.getCenter().y + vista.getSize().y);

    ///SETEADO DEL TRANSFORM
    setPosition(posicionCartel);
    setScale(escalaCartel);

    ///ajuste texto titulo
    _textoTitulo.setPosition((_sprFondo.getGlobalBounds().width/ 2) - (_textoTitulo.getGlobalBounds().width/2), 4);

    ///ajuste texto monedas
    _textoMonedas.setPosition(214,28);
    _textoMonedas.setOrigin(_textoMonedas.getGlobalBounds().width/2,0);

    //ajuste del selector
    float botonReclamarX1 = getPosition().x + (182  * getScale().x);
    float botonReclamarX2 = getPosition().x + (245 * getScale().x);
    float botonReclamarY1 = getPosition().y + (39 * getScale().y);
    float botonReclamarY2 = getPosition().y + (54 * getScale().y);

    _botonReclamar.set_dimenciones(botonReclamarX1, botonReclamarX2, botonReclamarY1, botonReclamarY2);
}

void MisionGUI::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(_sprFondo, states);

    target.draw(_textoTitulo, states);
    target.draw(_textoExplicacion, states);
    target.draw(_textoMonedas, states);

    target.draw(_sprBotonReclamar, states);
}


