#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Mob.h"
#include "Fantasma.h"
#include "Murcielago.h"
#include "Animal.h"
#include <memory>

class FabricaMobs
{
private:

    sf::Texture _fantasmaTexture;
    sf::Texture _murcielagoTexture;
    sf::Texture _vacaTexture;
    sf::Texture _ovejaTexture;
    sf::Texture _cerdoTexture;

public:
    FabricaMobs();
    std::unique_ptr<Mob> crearMobs(const std::string& tipo, sf::Vector2f posicion);

};
