#include "Item.h"
#include <iostream>
#include "json.hpp"
#include <fstream>


using namespace std;

/// Constructores
Item::Item(sf::Texture& texturaItems, int id){
    setCantidad(1);
       if (!_fuenteTextoCantidad.loadFromFile("PIXEARG_.TTF")){
        cout << "Error al cargar PIXEARG_.TTF" << endl;
    }
    sprItem.setTexture(texturaItems);

    _textoCantidad.setFont(_fuenteTextoCantidad);
    _textoCantidad.setOrigin(0.5,0.5);
    _textoCantidad.setFillColor(sf::Color::White);
    _textoCantidad.setCharacterSize(8);
    _textoCantidad.setOutlineThickness(0.8);
    _textoCantidad.setOutlineColor(sf::Color::Black);
    _textoCantidad.setStyle(sf::Text::Regular);

    sf::Texture& texture = const_cast<sf::Texture&>(_fuenteTextoCantidad.getTexture(8));
    texture.setSmooth(false);


    std::ifstream archivo("ItemsConfiguraciones.json");

    // Convertir ifstream a string
    std::stringstream buffer;
    buffer << archivo.rdbuf();
    std::string _contenidoParaJson = buffer.str();
    archivo.close();
    ConfiguracionItems = nlohmann::json::parse(_contenidoParaJson);

    setID(id);
}

Item::Item(){
    if (!_fuenteTextoCantidad.loadFromFile("PIXEARG_.TTF")){
        cout << "Error al cargar PIXEARG_.TTF" << endl;
    }

    _textoCantidad.setFont(_fuenteTextoCantidad);
    _textoCantidad.setOrigin(0.5,0.5);
    _textoCantidad.setFillColor(sf::Color::White);
    _textoCantidad.setCharacterSize(8);
    _textoCantidad.setOutlineThickness(0.8);
    _textoCantidad.setOutlineColor(sf::Color::Black);
    _textoCantidad.setStyle(sf::Text::Regular);

    ///Extraer la textura de la fuente y forsarla a no suavisarse
    sf::Texture& texture = const_cast<sf::Texture&>(_fuenteTextoCantidad.getTexture(8));
    texture.setSmooth(false);


    std::ifstream archivo("ItemsConfiguraciones.json");
    // Convertir ifstream a string
    std::stringstream buffer;
    buffer << archivo.rdbuf();
    std::string _contenidoParaJson = buffer.str();
    archivo.close();
    ConfiguracionItems = nlohmann::json::parse(_contenidoParaJson);

    setID(0);
}

void Item::setTexture(sf::Texture& texturaItems){
    sprItem.setTexture(texturaItems);
}

/// Getters
int Item::getID() const{
    return _id;
}
float Item::getPosX(){
    return _posX;
}
float Item::getPosY(){
    return _posY;
}


sf::Vector2f Item::getEscala(){
    return sprItem.getScale();
}
int Item::getCantidad(){
    return _cantidad;
}
int Item::getCantidadMax(){
    return _cantidadMax;
}
std::string Item::getTitulo(){
    return _titulo;
}
std::string Item::getDescripcion(){
    return _descripcion;
}

/// Setters
void Item::setID(int id){
    _id = id;
    actualizarPropiedades();
}
void Item::setPosX(float x){
    _posX = x;
}
void Item::setPosY(float y){
    _posY = y;
}

void Item::setEscala(sf::Vector2f nuevaEscala){
    sprItem.setScale(nuevaEscala);
    _textoCantidad.setScale(nuevaEscala);
}

void Item::setCantidad( int cantidad){
    if (cantidad < 1) _cantidad = 1;
    else _cantidad = cantidad;
    _textoCantidad.setString(to_string(getCantidad()));
}

void Item::setCantidadMax( int cantidadMax){
    _cantidadMax = cantidadMax;
}

void Item::setTitulo( string titulo){
    _titulo = titulo;
}

void Item::setDescripcion( string descripcion){
    _descripcion = descripcion;
}

/// Otros Metodos
void Item::actualizarSprite(){

    int columnasTextura = 9;
    int alturaFrame = 32;
    int anchuraFrame = 32;

    int frameX = anchuraFrame * (getID() % columnasTextura);
    int frameY = alturaFrame * (getID() / columnasTextura);

    sprItem.setTextureRect(sf::IntRect(frameX,frameY,anchuraFrame,alturaFrame));
    sprItem.setOrigin(16,16);

    sprItem.setPosition(getPosX(),getPosY());
    _textoCantidad.setPosition(getPosX(),getPosY()+5);

}

void Item::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(sprItem,states);
    if (_cantidad > 1){
        target.draw(_textoCantidad,states);
    }
}

void Item::actualizarPropiedades(){
    if (getID() != -1){
        setTitulo(ConfiguracionItems[getID()]["titulo"].get<string>());
        setDescripcion(ConfiguracionItems[getID()]["descripcion"].get<string>());
        setCantidadMax(ConfiguracionItems[getID()]["cantidad_maxima"].get<int>());
    }
}
