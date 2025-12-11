#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Cultivos.h"

class FabricaCultivos {
private:
    sf::Texture _texturaCultivos;

public:
    FabricaCultivos();
    //Recibe el ID del item (semilla) y te devuelve el cultivo
    std::unique_ptr<cultivo> crearDesdeSemilla(int idItemSemilla, float x, float y);
};
