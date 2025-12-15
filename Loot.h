#pragma once
#include <SFML/Graphics.hpp>
#include "Item.h"
#include "Colisionador.h"
#include <memory>
#include "FabricaItems.h"

class InventarioInterfaz; ///<<<== Consultar si es viable

class Loot : public sf::Transformable, public sf::Drawable
{
    private:
        std::unique_ptr<Item> _item;
        int _cantidad;
        int _timerReposo = 0;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        ///Variables para efectos
        float _incrementoSeno = 0;
        bool _looted = false;
    public:
        Loot( FabricaItems& fabItems, const sf::Vector2f& posicion, const int& id, int cantidad);
        void setPosicion(sf::Vector2f posicion);
        void update(const sf::Vector2f posicionJugador, InventarioInterfaz& inventario);
        bool getLooted();
};
