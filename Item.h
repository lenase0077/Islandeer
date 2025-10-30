#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "json.hpp"

/***
Notas:
Este objeto representa al tipo generico item junto con sus caracteristicas.
las principales son:
    -ID
    -Cantidad
    -Posicion
    -Escala
    -Descripcion
y con ellas brinda herramientas para permitir un control mas eficiente para los
inventarios y cofres.
*/

class Item : public sf::Drawable{
private:
    int _id; //define que item, de la lista de items, es. Afecta, principalmente, a la textura y descripcion
    int _cantidadMax;
    int _cantidad;
    float _posX, _posY; //Almacena y controla la posicion del item

    sf::Sprite sprItem;

    sf::Font _fuenteTextoCantidad;
    sf::Text _textoCantidad;

    std::string _descripcion;
    std::string _titulo;

     //Metodo que permite actualizar el sprite a la
                             //id correspondiente

    nlohmann::json ConfiguracionItems;
    std::string _contenidoParaJson;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:

    void actualizarSprite();

    /// Constructores
    Item(sf::Texture& texturaItems, int id);
    Item();
    Item(int id, int x, int y, int cantidad = 1);

    /// Getters
    int getID()const;
    float getPosX();
    float getPosY();
    sf::Vector2f getEscala();
    int getCantidad();
    int getCantidadMax();
    std::string getTitulo();
    std::string getDescripcion();

    /// Setters
    void setID(int id);
    void setPosX(float x);
    void setPosY(float y);
    void setEscala(sf::Vector2f nuevaEscala);
    void setCantidad( int cantidad);
    void setCantidadMax( int cantidadMax);
    void setTitulo( std::string titulo);
    void setDescripcion( std::string descripcion);


    /// Otros Metodos
    void actualizarSeleccion(sf::Vector2f posGlobalDelMouse, sf::Mouse mouse, bool &seleccionando);
    //void draw(sf::RenderWindow& window);

    void actualizarPropiedades();

};
