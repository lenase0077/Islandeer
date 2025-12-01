#pragma once
#include "Estructura.h"
#include "InventarioIntefaz.h"
#include "Item.h"
#include "FabricaItems.h"

class Cofre : public Estructura
{
private:
    InventarioInterfaz _inventarioCofre; // El cofre tiene su propio inventario

public:
    void update(const sf::Vector2f& posicionJugador, const sf::Vector2f& posGlobalDelMouse, const sf::View& vista, const float& relacionAspecto, InventarioInterfaz& inventarioJugador, std::list<Loot>& listaLoots);
    Cofre(sf::Texture& texturaBloques, float posX, float posY, int id, FabricaItems& fabItems);

};
