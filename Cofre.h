#pragma once
#include "Estructura.h"
#include "Item.h"

class Cofre : public Estructura
{
private:
    Item _contenido [30];
    bool _abierto = false;

public:
    Cofre(sf::Texture& texturaBloques, float posX, float posY, int id);
    Item* getContenido();
    bool estaAbierto();
    void setAbierto(bool estado);
};
