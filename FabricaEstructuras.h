#pragma once
#include "SFML/Graphics.hpp"
#include <list>
#include "Estructura.h"

class FabricaEstructuras
{
private:
    sf::Texture _texturaEstructuras;
    std::list<Estructura> _listaEstructuras;
public:
    FabricaEstructuras();
    void update();
    void crearEstructura(float x, float y, int ID);
};
