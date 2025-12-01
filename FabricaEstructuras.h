#pragma once
#include "SFML/Graphics.hpp"
#include <list>
#include "Estructura.h"
#include "MesaDeCrafteo.h"
#include "Horno.h"
#include "Arboles.h"
#include "Cofre.h"

class FabricaEstructuras
{
private:
    sf::Texture _texturaEstructuras;
    sf::Texture _texturaUIMesa;
    sf::Texture _texturaCopas;

    std::list<Estructura> _listaEstructuras;

    ///FABRICAS QUE NESESITAN ALGUNAS ESTRUCTURAS:
    FabricaItems* _fabItems = nullptr;
public:
    FabricaEstructuras(FabricaItems& fabItems);
    FabricaEstructuras();
    void update();
    std::unique_ptr<Estructura> crearEstructura(float x, float y, int ID);
    void insertarLootEntre(int ID, std::vector<int>& vectorLootsIDs, int minimo, int maximo);
};
