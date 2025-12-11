#pragma once
#include "Estructura.h"
#include "InventarioIntefaz.h"
#include "Item.h"

class Cofre : public Estructura
{
private:


public:
    void update(const sf::Vector2f& posicionJugador, const sf::Vector2f& posGlobalDelMouse, const sf::Mouse& mouse, const sf::View& vista, const float& relacionAspecto, InventarioInterfaz& inventario, float deltatime);
    Cofre(sf::Texture& texturaBloques, float posX, float posY, int id);

};
