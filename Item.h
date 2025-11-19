#pragma once
#include <SFML/Graphics.hpp>
#include "json.hpp"
#include <string>
#include <memory>

class Item : public sf::Drawable, public sf::Transformable{
private:
    int _id;
    int _cantidadMax;
    int _cantidad;
    float _posX, _posY;

    sf::Sprite sprItem;
    sf::Font _fuenteTextoCantidad;
    sf::Text _textoCantidad;
    std::string _descripcion;
    std::string _titulo;

    nlohmann::json ConfiguracionItems;
    std::string _contenidoParaJson;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
    /// Constructores
    Item(sf::Texture& texturaItems, int id);
    Item();

    // Destructor virtual
    virtual ~Item() = default;

    /// Getters
    int getID() const;
    sf::Vector2f getEscala() const;
    int getCantidad() const;
    int getCantidadMax() const;
    std::string getTitulo() const;
    std::string getDescripcion() const;

    /// Setters
    void setID(int id);
    void setEscala(sf::Vector2f nuevaEscala);
    void setCantidad(int cantidad);
    void setCantidadMax(int cantidadMax);
    void setTitulo(std::string titulo);
    void setDescripcion(std::string descripcion);

    void actualizarSprite();
};
