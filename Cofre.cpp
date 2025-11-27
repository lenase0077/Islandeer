#include <iostream>
#include "Cofre.h"
using namespace std;

Cofre::Cofre(sf::Texture& texturaBloques, float posX, float posY, int id)
 : Estructura (texturaBloques,posX,posY,id)
{
    setVida(100);
    _seRompePorColision = false;
}

void Cofre::update(const sf::Vector2f& posicionJugador, const sf::Vector2f& posGlobalDelMouse, const sf::Mouse& mouse, const sf::View& vista, const float& relacionAspecto, InventarioInterfaz& inventario, float deltatime)
{

}
