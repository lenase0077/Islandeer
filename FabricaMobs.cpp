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

    if(!_gallinaTexture.loadFromFile("Gallina.png")) {
        std::cout << "Error cargando Gallina.png" << std::endl;
    }
}

std::unique_ptr<Mob> FabricaMobs::crearMobs(const std::string& tipo, sf::Vector2f posicion)
{

    if (tipo == "Fantasma")
    {
        auto mob = std::make_unique<Fantasma>(_fantasmaTexture, posicion);
        mob->setVida(100);
        return mob;
    }

    if (tipo == "Murcielago")
    {
        auto mob = std::make_unique<Murcielago>(_murcielagoTexture, posicion);
        mob->setVida(100);
        return mob;
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

    if (tipo == "Gallina")
    {
        auto gallina = std::make_unique<Animal>(_gallinaTexture, posicion);
        gallina->caracteristicasDelAnimal(43 , false, 13);
        return gallina;
    }

    std::cout << "Tipo de enemigo desconocido" << std::endl;
    return nullptr;
}
