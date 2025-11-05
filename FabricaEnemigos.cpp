#include "FabricaEnemigos.h"
#include "Fantasma.h"
#include "Murcielago.h"
#include <iostream>

FabricaEnemigos::FabricaEnemigos()
{
    sf::Texture texturaFantasma;
    if(!texturaFantasma.loadFromFile("GatoFantasma-Sheet.png")) {
        std::cout << "Error cargando GatoFantasma-Sheet.png" << endl;
    }


    sf::Texture texturaMurcielago;
    if(!texturaMurcielago.loadFromFile("murcielago.png")) {
        std::cout << "Error cargando murcielago.png" << endl;
    }


}
