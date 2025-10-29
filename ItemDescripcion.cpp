#include <iostream>
#include "ItemDescripcion.h"
using namespace std;

void ItemDescripcion::setDescripcion (std::string descripcion){

    _textoDescripcion = descripcion;
    ActualizarDimensiones();
    EstablecerPosicion (_x , _y);
}

void ItemDescripcion::setTitulo (std::string titulo){
    _textoTitulo = titulo;
    ActualizarDimensiones();
    EstablecerPosicion (_x , _y);
}

string ItemDescripcion::getDescripcion(){
    return _textoDescripcion;
}

string ItemDescripcion::getTitulo(){
    return _textoTitulo;
}

ItemDescripcion::ItemDescripcion(float x , float y , int anchoMax){


    setVisible(true);
    _anchoMax = anchoMax;
    _margen = 10;

    ///Cargamos la fuente
    _fuente.loadFromFile("PIXEARG_.TTF");

    ///Editamos el titulo
    _titulo.setFont(_fuente);
    _titulo.setCharacterSize(20);
    _titulo.setFillColor(sf::Color::White);
    _titulo.setStyle(sf::Text::Bold);

    ///Editamos la descripcion
    _descripcion.setFont(_fuente);
    _descripcion.setCharacterSize(16);
    _descripcion.setFillColor(sf::Color::White);

    ///Editamos el fondo
    _fondo.setFillColor(sf::Color(123,29,255,200));
    _fondo.setOutlineColor(sf::Color::White); //Color Borde
    _fondo.setOutlineThickness(2); //Grosor Borde

    ///Textos por defectos
    _textoTitulo = "Titulo del item";
    _textoDescripcion = "Descripcion del item";


    ActualizarDimensiones();
    EstablecerPosicion (x , y);
}

ItemDescripcion::ItemDescripcion(){

    _anchoMax = 500;
    _margen = 10;

    setVisible(true);
    ///Cargamos la fuente
    _fuente.loadFromFile("PIXEARG_.TTF");

    ///Editamos el titulo
    _titulo.setFont(_fuente);
    _titulo.setCharacterSize(20);
    _titulo.setFillColor(sf::Color::White);
    _titulo.setStyle(sf::Text::Regular);

    ///Extraer la textura de la fuente y forsarla a no suavisarse
    sf::Texture& textureTexto = const_cast<sf::Texture&>(_fuente.getTexture(20));
    textureTexto.setSmooth(false);



    ///Editamos la descripcion
    _descripcion.setFont(_fuente);
    _descripcion.setCharacterSize(16);
    _descripcion.setFillColor(sf::Color::White);

    ///Editamos el fondo
    _fondo.setFillColor(sf::Color(123,29,255,200));
    _fondo.setOutlineColor(sf::Color::White); //Color Borde
    _fondo.setOutlineThickness(2); //Grosor Borde

    ///Textos por defectos
    _textoTitulo = "Titulo del item";
    _textoDescripcion = "Descripcion del item";

    ActualizarDimensiones();
    EstablecerPosicion (-100 , -100);
}

void ItemDescripcion::ActualizarDimensiones(){

    ///Aplicos los textos a los objetos de SFML
    _titulo.setString(_textoTitulo);

    ///Salto de linea en la descripcion
    string Lecturadescripcion = "";
    string desbordePostEspacio = "";

    int PosicionUltimoEspacio = 0;
    for (int i = 0 ; i < _textoDescripcion.size() ; i++){
        char caracter = _textoDescripcion[i];

        if (caracter == ' '){
            PosicionUltimoEspacio = i;
            desbordePostEspacio = "";
        }

        ///Agregamos caracter por caracter
        Lecturadescripcion += caracter;
        desbordePostEspacio += caracter;

        _descripcion.setString(Lecturadescripcion);

        ///Si se pasa del ancho maximo -> \n
        if (_descripcion.getLocalBounds().width >= _anchoMax - (_margen*2) && caracter!='\n'){
            _textoDescripcion[PosicionUltimoEspacio] = '\n';

            Lecturadescripcion = desbordePostEspacio;
        }
    }

    _descripcion.setString(_textoDescripcion);

    ///Calculamos el tamanio del texto
    ///getLocalBounds() -> devuelve el rect ngulo que contiene al texto
    float anchoTitulo = _titulo.getLocalBounds().width;
    float anchoDescripcion = _descripcion.getLocalBounds().width;

    float largoTitulo = _titulo.getLocalBounds().height;
    float largoDescripcion = _descripcion.getLocalBounds().height;

    ///Calculo el ancho necesario
    float anchoNecesario = max(anchoTitulo , anchoDescripcion) + (_margen * 2);
    float anchoFinal = min (anchoNecesario , _anchoMax);

    ///Calculo el alto necesario
    float altoNecesario = largoTitulo + largoDescripcion + (_margen * 3);

    ///Ajustamos el tamanio del fondo
    _fondo.setSize(sf::Vector2f(anchoFinal , altoNecesario));
}

void ItemDescripcion::EstablecerPosicion (float x , float y){

    _x = x;
    _y = y;

    ///Posicionamos el fondo
    _fondo.setPosition(x , y);

    ///Posicionamos el titulo
    _titulo.setPosition(x + _margen, y + _margen);

    ///Posicionamos la descripcion
    _descripcion.setPosition(x + _margen , y + _margen + _titulo.getLocalBounds().height + 15);

}



void ItemDescripcion::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    if(_visible){
        target.draw(_fondo,states);
        target.draw(_titulo,states);
        target.draw(_descripcion,states);
    }
}

bool ItemDescripcion::getVisible(){
    return _visible;
}

void ItemDescripcion::setVisible(bool nuevoEstado){
    _visible = nuevoEstado;
}

