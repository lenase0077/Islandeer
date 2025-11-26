#pragma once
#include "Estructura.h"
#include "SeleccionRectangulo.h"
#include "InventarioIntefaz.h"
#include <memory>
#include "Item.h"
#include "FabricaItems.h"

class MesaDeCrafteo : public Estructura
{
private:
    sf::Sprite _sprFondoMesa;
    SeleccionRectangulo _selectores[20];
    std::unique_ptr<Item> _items[20];
    FabricaItems _fabItems;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    bool _enUso = false;

    ///DEBUG
    sf::RectangleShape _selectoresDibujo[20];

public:
    virtual void update(const sf::Vector2f& posicionJugador, const sf::Vector2f& posGlobalDelMouse, const sf::Mouse& mouse, const sf::View& vista, const float& relacionAspecto, InventarioInterfaz& inventario);
    MesaDeCrafteo(sf::Texture& texturaBloques, sf::Texture& texturaUI, float posX, float posY, int id);
    void ajustarEscalaAutomaticamente(const sf::View& vista, const float& relacionAspecto);
    void controlDeItems(const sf::Vector2f& posGlobalDelMouse, InventarioInterfaz& inventario);
};

