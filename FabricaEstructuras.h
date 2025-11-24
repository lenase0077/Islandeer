#pragma once
#include "SFML/Graphics.hpp"
#include <list>
#include "Estructura.h"
#include "MesaDeCrafteo.h"

class FabricaEstructuras
{
private:
    sf::Texture _texturaEstructuras;
    sf::Texture _texturaUIMesa;
    std::list<Estructura> _listaEstructuras;
public:
    FabricaEstructuras();
    void update();
    std::unique_ptr<Estructura> crearEstructura(float x, float y, int ID);
    void insertarLootEntre(int ID, std::vector<int>& vectorLootsIDs, int minimo, int maximo);
};
