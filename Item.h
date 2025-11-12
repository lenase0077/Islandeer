#pragma once
#include <SFML/Graphics.hpp>
#include "json.hpp"
#include <string>

/***
Notas:
Este objeto representa al tipo generico item junto con sus caracteristicas.
las principales son:
    -ID
    -Cantidad
    -Posicion
    -Descripcion
y con ellas brinda herramientas para permitir un control mas eficiente para los
inventarios y cofres.
*/

class Item : public sf::Drawable, public sf::Transformable{
private:
    int _id; //define que item, de la lista de items, es.
    int _cantidadMax;
    int _cantidad;
    float _posX, _posY; //Almacena y controla la posicion del item

    sf::Sprite sprItem;

    sf::Font _fuenteTextoCantidad;
    sf::Text _textoCantidad;

    std::string _descripcion;
    std::string _titulo;

    nlohmann::json ConfiguracionItems; ///NO HACE FALTA CON FABRICA
    std::string _contenidoParaJson; ///NO HACE FALTA CON FABRICA
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:

    /// Constructores
    Item(sf::Texture& texturaItems, int id);
    Item();

    /// Getters
    int getID()const;
    sf::Vector2f getEscala();
    int getCantidad();
    int getCantidadMax();
    std::string getTitulo();
    std::string getDescripcion();

    /// Setters
    void setID(int id);
    void setEscala(sf::Vector2f nuevaEscala);
    void setCantidad( int cantidad);
    void setCantidadMax( int cantidadMax);
    void setTitulo( std::string titulo);
    void setDescripcion( std::string descripcion);

    void actualizarSprite(); //acomoda la parte de la textura que debe verse segun el sprite que le indiquemos

    /// Otros Metodos
    ///void actualizarPropiedades(); ///NO HACE FALTA CON FABRICA
    ///void setTexture(sf::Texture& texturaItems); ///NO HACE FALTA CON FABRICA

};
