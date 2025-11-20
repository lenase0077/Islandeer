#pragma once
#include "Estructura.h"
#include "SeleccionRectangulo.h"
#include "InventarioIntefaz.h"

class MesaDeCrafteo : public Estructura
{
private:
    sf::Texture* _texturaFondoMenu;
    SeleccionRectangulo _selectores[4];
    sf::Vector2f _posicionCartel;
    sf::Vector2f _escalaCartel;
    //virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
    virtual void update(const sf::Vector2f& posicionJugador, const sf::Vector2f& posGlobalDelMouse, const sf::Mouse& mouse, const sf::View& vista, const float& relacionAspecto, InventarioInterfaz& inventario);
    MesaDeCrafteo(sf::Texture& texturaBloques, float posX, float posY, int id);
};

