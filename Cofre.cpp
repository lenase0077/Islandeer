#include <iostream>
#include "Cofre.h"
using namespace std;

Cofre::Cofre(sf::Texture& texturaBloques, float posX, float posY, int id, FabricaItems& fabItems)
 : Estructura (texturaBloques,posX,posY,id),
 _inventarioCofre(fabItems)
{
    setVida(100);
    _seRompePorColision = false;
}

void Cofre::update(const sf::Vector2f& posicionJugador, const sf::Vector2f& posGlobalDelMouse, const sf::View& vista, const float& relacionAspecto, InventarioInterfaz& inventarioJugador, std::list<Loot>& listaLoots)
{
    // 1. Detectar si el jugador interact£a para abrir el cofre
    // (Tu l¢gica de abrir/cerrar aqu¡...)

    if (_inventarioCofre.getAbierto())
    {
        // 2. ENLACE MAGICO:
        // Le pasamos al cofre el puntero del item en mano del JUGADOR
        _inventarioCofre.enlazarItemEnMano(inventarioJugador.obtenerPunteroItemEnMano());

        // 3. Actualizamos el inventario del cofre
        _inventarioCofre.update(posGlobalDelMouse, vista, relacionAspecto, listaLoots);
        //void InventarioInterfaz::update(const sf::Vector2f& posGlobalDelMouse, const sf::View& vista, const float& relacionAspecto, std::list<Loot>& listaLoots)
    }
    else
    {
        // Si se cierra, desenlazamos por seguridad (opcional)
        _inventarioCofre.enlazarItemEnMano(nullptr);
    }
}
