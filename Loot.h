#pragma once
#include <SFML/Graphics.hpp>
#include "Item.h"
#include "Colisionador.h"
#include "InventarioIntefaz.h"

class Loot : public sf::Transformable, public sf::Drawable
{
    private:
        Item _item;
        int _cantidad;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        ///Variables para efectos
        float _incrementoSeno;
        bool _looted = false;
    public:
        Loot( sf::Texture& texturaItems,const sf::Vector2f& posicion, const int& id);
        void setPosicion(sf::Vector2f posicion);
        void update(const sf::Vector2f posicionJugador, InventarioInterfaz& inventario);
        bool getLooted();
};
