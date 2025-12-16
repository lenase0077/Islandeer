#pragma once
#include <SFML/Graphics.hpp>
#include "json.hpp"
#include <string>
#include <memory>

enum class TipoMaterial { MADERA, NADA, PIEDRA, HIERRO, DIAMANTE, CARNE};

class Item : public sf::Drawable, public sf::Transformable{
private:
    int _id;
    int _cantidadMax;
    int _cantidad;
    float _posX, _posY;

    sf::Text _textoCantidad;
    std::string _descripcion;
    std::string _titulo;

    nlohmann::json ConfiguracionItems;
    std::string _contenidoParaJson;

    static sf::Font _fuenteTextoCantidad;

protected:
        sf::Sprite sprItem;
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
    void setColor(sf::Color color);
    void setID(int id);
    void setEscala(sf::Vector2f nuevaEscala);
    void setCantidad(int cantidad);
    void setCantidadMax(int cantidadMax);
    void setTitulo(std::string titulo);
    void setDescripcion(std::string descripcion);

    void actualizarSprite();


    virtual float obtenerFuerza(TipoMaterial material) const;
    virtual void usar();
    virtual bool estaRota() const;
    // necesite un getter pa pasarle a la animacion
    const sf::Sprite& getSprite() const { return sprItem; }
};
