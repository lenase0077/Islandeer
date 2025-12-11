#pragma once
#include <SFML/Graphics.hpp>
#include "json.hpp"
#include "Item.h"
#include <memory>
#include <string>
#include "Herramienta.h"
#include <map>
// usar esto

struct DatosHerramienta {
    float durabilidad;
    float danioBase;
    std::map<TipoMaterial, float> multiplicadores;
};

class FabricaItems
{
private:
    sf::Texture _texturaItems;
    nlohmann::json _ConfiguracionItems;

    std::map<int, DatosHerramienta> _datosHerramientas;
    void cargarDatosHerramientas();
    TipoMaterial stringAEnum(std::string sJson);


public:
    std::unique_ptr<Item> crearItem(int id);
    FabricaItems( sf::Texture& texturaItems,  nlohmann::json& ConfiguracionItems);
    FabricaItems();
};
