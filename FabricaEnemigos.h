#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Mob.h"
#include <memory>


class FabricaEnemigos
{
private:

    sf::Texture _fantasmaTexture;
    sf::Texture _murcielagoTexture;





public:
    FabricaEnemigos();
    std::unique_ptr<Mob> crearEnemigo(const std::string& tipo, sf::Vector2f posicion;


};
