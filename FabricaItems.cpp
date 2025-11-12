#include "FabricaItems.h"


FabricaItems::FabricaItems(sf::Texture& texturaItems, nlohmann::json& ConfiguracionItems){
    _texturaItems = &texturaItems;
    _ConfiguracionItems = &ConfiguracionItems;
}

std::unique_ptr<Item> FabricaItems::crearItem(int id){

    auto nuevoItem = std::make_unique<Item>(*_texturaItems, id);
    nuevoItem -> setTitulo(_ConfiguracionItems[id]["titulo"].get<std::string>());
    nuevoItem -> setDescripcion(_ConfiguracionItems[id]["descripcion"].get<std::string>());
    nuevoItem -> setCantidadMax(_ConfiguracionItems[id]["cantidad_maxima"].get<int>());
    return nuevoItem;

}
