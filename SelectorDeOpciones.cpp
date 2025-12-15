#include "SelectorDeOpciones.h"


SelectorDeOpciones::SelectorDeOpciones(const std::string& tituloOpcion,const sf::Font& fuenteTexto){
    _titulo.setFont(fuenteTexto);
    _titulo.setString(tituloOpcion);
    _titulo.setCharacterSize(8);
    _titulo.setScale(1.8,1.8);

    _fuenteOpciones = &fuenteTexto;
    _fondo.setFillColor(sf::Color(0,0,0,200));

    _resaltadoSeleccion.setFillColor(sf::Color(255,255,255,100));
}

void SelectorDeOpciones::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    states.transform *= getTransform();

    target.draw(_fondo,states);

    target.draw(_titulo,states);

    for (auto& textoAnalizado : _textoOpciones){
        target.draw(textoAnalizado,states);
    }

    target.draw(_resaltadoSeleccion,states);
}

void SelectorDeOpciones::setAbierto(bool nuevoEstado){
    _abierto = nuevoEstado;
}
bool SelectorDeOpciones::getAbierto(){
    return _abierto;
}

void SelectorDeOpciones::update(const sf::Vector2f& posGlobalDelMouse, InventarioInterfaz& inventarioJugador){
    Comandos& input = Comandos::getInstancia();

    int fila = 0;
    bool sobreUna = false;
    for (auto& textoAnalizado : _textoOpciones){
        if(_selectoresOpciones[fila].estaDentro(posGlobalDelMouse.x,posGlobalDelMouse.y,true)){
            sobreUna = true;
            _resaltadoSeleccion.setPosition(0,16*(fila+1));
            if (input.mouseIzqRecienPresionado){
                _opcionSeleccionada = fila;
            }
        }
        fila++;
    }
    if (!sobreUna){
        _resaltadoSeleccion.setPosition(0,1000);
    }

}
void SelectorDeOpciones::ajustarEscalaAutomaticamente(const sf::View& vista, const float& relacionAspecto){
    sf::Vector2f escalaCartel(sf::Vector2f(vista.getSize().x/512, vista.getSize().y/512 * relacionAspecto));

    // Calcula posiciones

    sf::Vector2f posicionCartel;
    ///de esta forma logro adaptarlo a la cantidad de opciones
    float posY = (vista.getCenter().y - vista.getSize().y/2) + (vista.getSize().y - 16 * (_textoOpciones.size() + 1));

    if (_abierto) posicionCartel = sf::Vector2f(vista.getCenter().x-vista.getSize().x/2, posY);
    else posicionCartel = sf::Vector2f(vista.getCenter().x - vista.getSize().x/2, vista.getCenter().y + vista.getSize().y);

    ///SETEADO DEL TRANSFORM
    setPosition(posicionCartel);
    setScale(escalaCartel);

    float alturaFondo = (_textoOpciones.size() + 1) * 16 + 12;
    _fondo.setSize({1000.0,alturaFondo});
    _fondo.setPosition(0,-8);

    _titulo.setPosition(5,0);

    _resaltadoSeleccion.setSize({1000,16});


    int fila = 0;
    float selecX1, selecX2, selecY1, selecY2;
    for (auto& textoAnalizado : _textoOpciones){
        textoAnalizado.setPosition(5,10+16*(fila+1));
        textoAnalizado.setOrigin(0,textoAnalizado.getGlobalBounds().height/2);

        selecX1 = getPosition().x;
        selecX2 = getPosition().x + 1000*getScale().x;
        selecY1 = getPosition().y + 16*getScale().y + fila*16*getScale().y;
        selecY2 = getPosition().y + 16*getScale().y + (fila+1)*16*getScale().y;

        _selectoresOpciones[fila].set_dimenciones(selecX1, selecX2, selecY1, selecY2);

        fila++;
    }

}

void SelectorDeOpciones::agregarOpcion(std::string tituloOpcion){
    sf::Text textoDefault;
    textoDefault.setFont(*_fuenteOpciones);
    textoDefault.setCharacterSize(8);
    textoDefault.setScale(1.2,1.2);
    textoDefault.setString(tituloOpcion);
    _textoOpciones.push_back(textoDefault);
    _selectoresOpciones.push_back(SeleccionRectangulo());
}

int SelectorDeOpciones::getOpcionSeleccionada(){
    return _opcionSeleccionada;
}

void SelectorDeOpciones::resetOpcionSeleccionada(){
    _opcionSeleccionada = -1;
}
