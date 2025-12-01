#pragma once
#include "Estructura.h"
#include "InventarioIntefaz.h"
#include "Item.h"
#include "FabricaItems.h"

class Cofre : public Estructura
{
private:
    bool _abierto = true;
public:
    void update(const sf::Vector2f& posicionJugador, const sf::Vector2f& posGlobalDelMouse, const sf::View& vista, const float& relacionAspecto, InventarioInterfaz& inventario, InventarioInterfaz& inventarioCofre, float deltatime) override;
    Cofre(sf::Texture& texturaBloques, float posX, float posY, int id);
    bool getAbierto();

};
