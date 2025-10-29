#pragma once
#include "Item.h"
#include "SeleccionRectangulo.h"
#include <SFML/Graphics.hpp>

class InventarioResumido : public sf::Drawable, sf::Transformable{
private:
    Item _items[10];
    SeleccionRectangulo _selectores[10];
    int _slotSeleccionado;
    sf::Texture _texturaFondo;
    sf::Sprite _sprFondo;
    sf::RectangleShape _rectanguloSlotSeleccionado;
    sf::Font _fuenteTextoTitulo;
    sf::Text _textoTitulo;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
    InventarioResumido();
    ///SETTERS
    void setItems( Item vectorItems[]); ///Este Setter se usara principalmente por el InventarioInterfaz
    void setSlotSeleccionado(int slot);
    void setPosicion(float x, float y);
    void setEscala(float escalaX, float escalaY);

    ///GETTERS
    int getSlotSeleccionado();
    Item getItem(int slot);

    ///OTROS METODOS
    void update(const sf::View& vista, const float& relacionAspecto);
    void cambiarSlotsConEventos(sf::Event& evento);


};
