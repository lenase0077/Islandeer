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
    _textoCantidad.setFillColor(sf::Color::White);
    _textoCantidad.setCharacterSize(8);
    _textoCantidad.setOutlineThickness(0.8);
    _textoCantidad.setOutlineColor(sf::Color::Black);
    _textoCantidad.setStyle(sf::Text::Regular);

    _id = id;

    // Ajustamos smoothing del atlas de la fuente (si aplica)
    sf::Texture& texture = const_cast<sf::Texture&>(_fuenteTextoCantidad.getTexture(8));
    texture.setSmooth(false);

    // Actualizamos string y origen correctamente
    _textoCantidad.setString(to_string(_cantidad));
    sf::FloatRect tb = _textoCantidad.getLocalBounds();
    _textoCantidad.setOrigin(tb.left + tb.width/2.0f, tb.top + tb.height/2.0f);

    // Actualizo rect del sprite en base al id
    actualizarSprite();
}

Item::Item(){
    if (!_fuenteTextoCantidad.loadFromFile("PIXEARG_.TTF")){
        cout << "Error al cargar PIXEARG_.TTF" << endl;
    }

    _textoCantidad.setFont(_fuenteTextoCantidad);
    _textoCantidad.setFillColor(sf::Color::White);
    _textoCantidad.setCharacterSize(8);
    _textoCantidad.setOutlineThickness(0.8);
    _textoCantidad.setOutlineColor(sf::Color::Black);
    _textoCantidad.setStyle(sf::Text::Regular);

    ///Extraer la textura de la fuente y forsarla a no suavizarse
    sf::Texture& texture = const_cast<sf::Texture&>(_fuenteTextoCantidad.getTexture(8));
    texture.setSmooth(false);

    _id = 1;
    setCantidad(1);

    _textoCantidad.setString(to_string(_cantidad));
    sf::FloatRect tb = _textoCantidad.getLocalBounds();
    _textoCantidad.setOrigin(tb.left + tb.width/2.0f, tb.top + tb.height/2.0f);
}

/*void Item::setTexture(sf::Texture& texturaItems){
    sprItem.setTexture(texturaItems);
}*/

/// Getters
int Item::getID() const{
    return _id;
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
    // Si el sprite tiene textura, actualizo su rect según el id
    actualizarSprite();
}

void Item::setEscala(sf::Vector2f nuevaEscala){
    sprItem.setScale(nuevaEscala);
    _textoCantidad.setScale(nuevaEscala);
}

void Item::setCantidad( int cantidad){
    if (cantidad < 1) _cantidad = 1;
    else _cantidad = cantidad;
    _textoCantidad.setString(to_string(getCantidad()));
    // re-centro el texto después de cambiar el string
    sf::FloatRect tb = _textoCantidad.getLocalBounds();
    _textoCantidad.setOrigin(tb.left + tb.width/2.0f, tb.top + tb.height/2.0f);
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

    // Asegurarse de que la textura esté definida antes de usarla
    if (!sprItem.getTexture()) return;

    int columnasTextura = 9;
    int alturaFrame = 32;
    int anchuraFrame = 32;

    int frameX = anchuraFrame * (getID() % columnasTextura);
    int frameY = alturaFrame * (getID() / columnasTextura);

    sprItem.setTextureRect(sf::IntRect(frameX,frameY,anchuraFrame,alturaFrame));
    sprItem.setOrigin(16,16);

    sprItem.setPosition(0, 0);

    // Coloco el contador debajo del centro
    _textoCantidad.setPosition(0, 5);
}

void Item::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    states.transform *= getTransform();
    target.draw(sprItem,states);
    if (_cantidad > 1){
        target.draw(_textoCantidad,states);
    }
}
