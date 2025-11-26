#include "FabricaMobs.h"
#include <iostream>

FabricaMobs::FabricaMobs()
{
    if(!_fantasmaTexture.loadFromFile("GatoFantasma-Sheet.png")) {
        std::cout << "Error cargando GatoFantasma-Sheet.png" << std::endl;
    }

    if(!_murcielagoTexture.loadFromFile("murcielago.png")) {
        std::cout << "Error cargando murcielago.png" << std::endl;
    }

    if(!_vacaTexture.loadFromFile("White_Cow.png")) {
        std::cout << "Error cargando Vaca.png" << std::endl;
    }

    if(!_ovejaTexture.loadFromFile("Sheep.png")) {
        std::cout << "Error cargando Oveja.png" << std::endl;
    }

    if(!_cerdoTexture.loadFromFile("Pig.png")) {
        std::cout << "Error cargando Cerdo.png" << std::endl;
    }
}

std::unique_ptr<Mob> FabricaMobs::crearMobs(const std::string& tipo, sf::Vector2f posicion)
{

    if (tipo == "Fantasma")
    {
        return std::make_unique<Fantasma>(_fantasmaTexture, posicion);
    }

    if (tipo == "Murcielago")
    {
        return std::make_unique<Murcielago>(_murcielagoTexture, posicion);
    }

    if (tipo == "Vaca")
    {
        auto vaca = std::make_unique<Animal>(_vacaTexture, posicion);
        vaca->caracteristicasDelAnimal(47 , true);
        return vaca;
    }

    if (tipo == "Oveja")
    {
        auto oveja = std::make_unique<Animal>(_ovejaTexture, posicion);
        oveja->caracteristicasDelAnimal(-1 , false);
        return oveja;
    }

    if (tipo == "Cerdo")
    {
        auto cerdo = std::make_unique<Animal>(_cerdoTexture, posicion);
        cerdo->caracteristicasDelAnimal(45 , false);
        return cerdo;
    }

    std::cout << "Tipo de enemigo desconocido" << std::endl;
    return nullptr;
}
