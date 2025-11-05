#include "FabricaEnemigos.h"
#include "Fantasma.h"
#include "Murcielago.h"
#include <iostream>

FabricaEnemigos::FabricaEnemigos()
{
    if(!_fantasmaTexture.loadFromFile("GatoFantasma-Sheet.png")) {
        std::cout << "Error cargando GatoFantasma-Sheet.png" << std::endl;
    }


    if(!_murcielagoTexture.loadFromFile("murcielago.png")) {
        std::cout << "Error cargando murcielago.png" << std::endl;
    }


}

std::unique_ptr<Mob> FabricaEnemigos::crearEnemigo(const std::string& tipo, sf::Vector2f posicion)
{

    if (tipo == "Fantasma")
    {
        return std::make_unique<Fantasma>(_fantasmaTexture, posicion);
    }


    if (tipo == "Murcielago")
    {
        return std::make_unique<Murcielago>(_murcielagoTexture, posicion);
    }

    std::cout << "Tipo de enemigo desconocido" << std::endl;
    return nullptr;
}
