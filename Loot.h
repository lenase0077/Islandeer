#pragma once
#include <SFML/Graphics.hpp>
#include "Item.h"
#include "Colisionador.h"

class Loot : public sf::Transformable, public sf::Drawable
{
    private:
        Item _item;
        int _cantidad;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        Colisionador _colisionConJugador;
        ///Variables para efectos
        float _incrementoSeno;
    public:
        Loot(const sf::Vector2f& posicion, const int& id, const int& cantidad);
        void setPosicion(sf::Vector2f posicion);
        void update();
};
