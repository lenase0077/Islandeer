#pragma once
#include <SFML/Graphics.hpp>
#include "json.hpp"
#include "Item.h"
#include <memory>
#include <string>

class FabricaItems
{
private:
    sf::Texture _texturaItems;
    nlohmann::json _ConfiguracionItems;
public:
    std::unique_ptr<Item> crearItem(int id);
    FabricaItems( sf::Texture& texturaItems,  nlohmann::json& ConfiguracionItems);
    FabricaItems();
};
