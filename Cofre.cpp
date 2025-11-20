#include <iostream>
#include "Cofre.h"
using namespace std;

Cofre::Cofre(sf::Texture& texturaBloques, float posX, float posY, int id)
: Estructura (texturaBloques,posX,posY,id)
{
    for (int i = 0; i < 30; i++)
    {
        _contenido[i].setID(-1);
        _contenido[i].setCantidad(0);
    }
}

Item* Cofre::getContenido()
{
    return _contenido;
}

bool Cofre::estaAbierto()
{
    return _abierto;
}

void Cofre::setAbierto(bool estado)
{
    _abierto = estado;
}
