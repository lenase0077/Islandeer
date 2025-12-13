#include "InterfazBarcoHuida.h"
#include "Comando.h"
#include <iostream>

using namespace std;

InterfazBarcoHuida::InterfazBarcoHuida(const sf::Texture& texturaFondoInterfaz){
    _texturaFondoInterfaz = &texturaFondoInterfaz;
    _sprfondoInterfaz.setTexture(texturaFondoInterfaz);

    _titulos[0] = "Kit de Construcci¢n Naval";
    _titulos[1] = "Suministros y Cocina";
    _titulos[2] = "Hidrataci¢n y Almacenamiento";
    _titulos[3] = "Seguridad y Salud Mental";

    ///FUENTE LOCAL TEMPORAL, NO SE ASUSTEN
    if (_fuenteTexto.getInfo().family == "") {
        if (!_fuenteTexto.loadFromFile("PIXEARG_.TTF")){
            cout << "Error al cargar PIXEARG_.TTF" << endl;
        }
        const_cast<sf::Texture&>(_fuenteTexto.getTexture(8)).setSmooth(false);
    }
    _textoTitulo.setFont(_fuenteTexto);
    _textoTitulo.setCharacterSize(8);
}

void InterfazBarcoHuida::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    states.transform *= getTransform();
    target.draw(_sprfondoInterfaz, states);
    target.draw(_textoTitulo, states);
}

void InterfazBarcoHuida::update(const sf::Vector2f& posGlobalDelMouse, InventarioInterfaz& inventarioJugador){

    Comandos& input = Comandos::getInstancia();

    if (_botonDerControlPagina.estaDentro(posGlobalDelMouse.x,posGlobalDelMouse.y,input.mouseIzqRecienPresionado)){
        if (_pagina < 3) _pagina++;
        else _pagina = 0;
    }
    else if (_botonIzqControlPagina.estaDentro(posGlobalDelMouse.x,posGlobalDelMouse.y,input.mouseIzqRecienPresionado)){
        if (_pagina > 0) _pagina--;
        else _pagina = 3;
    }

    cout << "Pagina actual: " << _pagina << endl;

    _textoTitulo.setString(_titulos[_pagina]);
}

void InterfazBarcoHuida::ajustarEscalaAutomaticamente(const sf::View& vista, const float& relacionAspecto){
    // Escala proporcional al tamanio de la vista
    sf::Vector2f escalaCartel(sf::Vector2f(vista.getSize().x/512, vista.getSize().y/512 * relacionAspecto));

    float centroX = ((_sprfondoInterfaz.getGlobalBounds().width/ 2)) * escalaCartel.x;

    // Calcula posiciones
    sf::Vector2f posicionCartel(vista.getCenter().x - centroX, vista.getCenter().y- vista.getSize().y/2.5);

    ///SETEADO DEL TRANSFORM
    setPosition(posicionCartel);
    setScale(escalaCartel);


    _textoTitulo.setPosition(127 - _textoTitulo.getGlobalBounds().width / 2, 40);

    ///SETEADO DE LAS DIMENCIONES DE LOS BOTONES SigPag y PagAnterior
    float botonIzqX1 = getPosition().x + (5  * getScale().x);
    float botonIzqX2 = getPosition().x + (28 * getScale().x);
    float botonIzqY1 = getPosition().y + (37 * getScale().y);
    float botonIzqY2 = getPosition().y + (60 * getScale().y);

    _botonIzqControlPagina.set_dimenciones( botonIzqX1, botonIzqX2, botonIzqY1, botonIzqY2);

    float botonDerX1 = getPosition().x + (229  * getScale().x);
    float botonDerX2 = getPosition().x + (252  * getScale().x);
    float botonDerY1 = getPosition().y + (37   * getScale().y);
    float botonDerY2 = getPosition().y + (60   * getScale().y);

    _botonDerControlPagina.set_dimenciones( botonDerX1, botonDerX2, botonDerY1, botonDerY2);


}
