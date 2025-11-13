#include "Item.h"
#include <iostream>
#include "json.hpp"
#include <fstream>

using namespace std;

/// Constructores

// Constructor principal - crea item con textura e ID específico
Item::Item(sf::Texture& texturaItems, int id){
    setCantidad(1); // Inicializa con cantidad 1

    // Carga fuente para mostrar cantidad
    if (!_fuenteTextoCantidad.loadFromFile("PIXEARG_.TTF")){
        cout << "Error al cargar PIXEARG_.TTF" << endl;
    }
    sprItem.setTexture(texturaItems); // Asigna textura del atlas de items

    // Configura texto de cantidad
    _textoCantidad.setFont(_fuenteTextoCantidad);
    _textoCantidad.setFillColor(sf::Color::White);
    _textoCantidad.setCharacterSize(8);
    _textoCantidad.setOutlineThickness(0.8);
    _textoCantidad.setOutlineColor(sf::Color::Black);
    _textoCantidad.setStyle(sf::Text::Regular);

    _id = id; // Establece ID del item

    // Ajustamos smoothing del atlas de la fuente (si aplica)
    sf::Texture& texture = const_cast<sf::Texture&>(_fuenteTextoCantidad.getTexture(8));
    texture.setSmooth(false); // Fuente pixelada

    // Actualizamos string y origen correctamente
    _textoCantidad.setString(to_string(_cantidad));
    sf::FloatRect tb = _textoCantidad.getLocalBounds();
    _textoCantidad.setOrigin(tb.left + tb.width/2.0f, tb.top + tb.height/2.0f); // Centra texto

    // Actualizo rect del sprite en base al id
    actualizarSprite(); // Configura frame correcto del atlas
}

// Constructor por defecto
Item::Item(){
    // Carga fuente
    if (!_fuenteTextoCantidad.loadFromFile("PIXEARG_.TTF")){
        cout << "Error al cargar PIXEARG_.TTF" << endl;
    }

    // Configura texto
    _textoCantidad.setFont(_fuenteTextoCantidad);
    _textoCantidad.setFillColor(sf::Color::White);
    _textoCantidad.setCharacterSize(8);
    _textoCantidad.setOutlineThickness(0.8);
    _textoCantidad.setOutlineColor(sf::Color::Black);
    _textoCantidad.setStyle(sf::Text::Regular);

    ///Extraer la textura de la fuente y forsarla a no suavizarse
    sf::Texture& texture = const_cast<sf::Texture&>(_fuenteTextoCantidad.getTexture(8));
    texture.setSmooth(false); // Textura pixelada

    _id = 1; // ID por defecto
    setCantidad(1); // Cantidad por defecto

    _textoCantidad.setString(to_string(_cantidad));
    sf::FloatRect tb = _textoCantidad.getLocalBounds();
    _textoCantidad.setOrigin(tb.left + tb.width/2.0f, tb.top + tb.height/2.0f); // Centra texto
}

/// MÉTODO CLONE - Implementación del patrón Prototype
std::unique_ptr<Item> Item::clone() const {
    // Crear un nuevo Item usando el constructor de copia por defecto
    auto nuevoItem = std::make_unique<Item>();

    // Copiar manualmente todos los atributos (copia profunda)
    nuevoItem->_id = _id;
    nuevoItem->_cantidad = _cantidad;
    nuevoItem->_cantidadMax = _cantidadMax;
    nuevoItem->_descripcion = _descripcion;
    nuevoItem->_titulo = _titulo;

    // Copiar el sprite (si tiene textura)
    if (sprItem.getTexture()) {
        nuevoItem->sprItem.setTexture(*sprItem.getTexture());
        nuevoItem->sprItem.setTextureRect(sprItem.getTextureRect()); // Mismo frame
    }
    nuevoItem->sprItem.setScale(sprItem.getScale());
    nuevoItem->sprItem.setOrigin(sprItem.getOrigin());

    // Copiar el texto
    nuevoItem->_textoCantidad = _textoCantidad;
    nuevoItem->_fuenteTextoCantidad = _fuenteTextoCantidad;

    return nuevoItem; // Devuelve copia exacta
}

/// Getters - Métodos de acceso a atributos privados
int Item::getID() const{
    return _id;
}

sf::Vector2f Item::getEscala() const{
    return sprItem.getScale();
}

int Item::getCantidad() const{
    return _cantidad;
}

int Item::getCantidadMax() const{
    return _cantidadMax;
}

std::string Item::getTitulo() const{
    return _titulo;
}

std::string Item::getDescripcion() const{
    return _descripcion;
}

/// Setters - Métodos para modificar atributos

void Item::setID(int id){
    _id = id;
    actualizarSprite(); // Actualiza frame del sprite cuando cambia ID
}

void Item::setEscala(sf::Vector2f nuevaEscala){
    sprItem.setScale(nuevaEscala);
    _textoCantidad.setScale(nuevaEscala); // Escala texto también
}

void Item::setCantidad(int cantidad){
    if (cantidad < 1) _cantidad = 1; // Mínimo 1
    else _cantidad = cantidad;
    _textoCantidad.setString(to_string(getCantidad())); // Actualiza texto
    sf::FloatRect tb = _textoCantidad.getLocalBounds();
    _textoCantidad.setOrigin(tb.left + tb.width/2.0f, tb.top + tb.height/2.0f); // Re-centra
}

void Item::setCantidadMax(int cantidadMax){
    _cantidadMax = cantidadMax;
}

void Item::setTitulo(string titulo){
    _titulo = titulo;
}

void Item::setDescripcion(string descripcion){
    _descripcion = descripcion;
}

/// Otros Metodos

// Actualiza el frame del sprite según el ID (sprite sheet)
void Item::actualizarSprite(){
    if (!sprItem.getTexture()) return; // Verifica que tenga textura

    int columnasTextura = 9; // Atlas tiene 9 columnas
    int alturaFrame = 32;
    int anchuraFrame = 32;

    // Calcula posición del frame en el atlas
    int frameX = anchuraFrame * (getID() % columnasTextura);
    int frameY = alturaFrame * (getID() / columnasTextura);

    sprItem.setTextureRect(sf::IntRect(frameX,frameY,anchuraFrame,alturaFrame));
    sprItem.setOrigin(16,16); // Centro del sprite
    sprItem.setPosition(0, 0);

    _textoCantidad.setPosition(0, 5); // Posición del texto (abajo del item)
}

// Método de dibujo requerido por SFML
void Item::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    states.transform *= getTransform(); // Aplica transformaciones
    target.draw(sprItem,states); // Dibuja sprite del item

    // Solo muestra cantidad si es mayor a 1
    if (_cantidad > 1){
        target.draw(_textoCantidad,states); // Dibuja texto de cantidad
    }
}
