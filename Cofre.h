#pragma once
#include "Estructura.h"
#include "InventarioIntefaz.h"
#include "Item.h"
#include "FabricaItems.h"
#include <array>
#include <memory>

class Cofre : public Estructura
{
private:
    bool _abierto = true;
    std::array<std::unique_ptr<Item>, 30> _itemsGuardados;

public:
    void update(const sf::Vector2f& posicionJugador, const sf::Vector2f& posGlobalDelMouse, const sf::View& vista, const float& relacionAspecto, InventarioInterfaz& inventario, InventarioInterfaz& inventarioCofre, float deltatime) override;
    Cofre(sf::Texture& texturaBloques, float posX, float posY, int id);
    bool getAbierto();

    void guardarContenido(InventarioInterfaz& inventarioCofre);
    void cargarContenido(InventarioInterfaz& inventarioCofre);
};
