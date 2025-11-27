#pragma once
#include "Estructura.h"
#include "InventarioIntefaz.h"
#include "InventarioResumidoInterfaz.h"
#include "FabricaItems.h"
#include <list>

class Horno : public Estructura
{
private:
    bool _estaCocinando;
    float _tiempoCoccionActual;
    float _tiempoParaCocinar;
    int _idProductoCocinandose;
    bool fueClickeado(const sf::Vector2f& posMouse);
    int IDProductoCocinable(int IDItem);

public:
    Horno(sf::Texture& texturaBloques, float posX, float posY, int id);
    void update(const sf::Vector2f& posicionJugador, const sf::Vector2f& posGlobalDelMouse, const sf::Mouse& mouse, const sf::View& vista, const float& relacionAspecto, InventarioInterfaz& inventario, float deltatime);
    void soltarLoot(FabricaItems& fabItems, std::list<Loot>& listaLoot);
    bool terminarDeCocinar();
};
