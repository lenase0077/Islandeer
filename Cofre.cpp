#include <iostream>
#include "Cofre.h"
using namespace std;

Cofre::Cofre(sf::Texture& texturaBloques, float posX, float posY, int id)
 : Estructura (texturaBloques,posX,posY,id)
{
    setVida(100);
    _seRompePorColision = false;
}

void Cofre::update(const sf::Vector2f& posicionJugador, const sf::Vector2f& posGlobalDelMouse, const sf::View& vista, const float& relacionAspecto, InventarioInterfaz& inventario, InventarioInterfaz& inventarioCofre, float deltatime)
{
    // 1. Detectar si el jugador interact£a para abrir el cofre
    // (Tu l¢gica de abrir/cerrar aqu¡...)

    if (inventarioCofre.getAbierto())
    {
        // 2. ENLACE MAGICO:
        // Le pasamos al cofre el puntero del item en mano del JUGADOR
        inventarioCofre.enlazarItemEnMano(inventario.obtenerPunteroItemEnMano());

        // 3. Actualizamos el inventario del cofre

        //void InventarioInterfaz::update(const sf::Vector2f& posGlobalDelMouse, const sf::View& vista, const float& relacionAspecto, std::list<Loot>& listaLoots)
    }
    else
    {
        // Si se cierra, desenlazamos por seguridad (opcional)
        inventarioCofre.enlazarItemEnMano(nullptr);
    }
}

bool Cofre::getAbierto(){
    return _abierto;
}
