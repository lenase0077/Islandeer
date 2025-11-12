#include "FabricaItems.h"
#include <fstream>
#include <iostream>

FabricaItems::FabricaItems(){
    ///CARGA DE JSON DE ITEMS ===========================================
    std::ifstream archivo("ItemsConfiguraciones.json");
    // Convertir ifstream a string
    std::stringstream buffer;
    buffer << archivo.rdbuf();
    std::string contenidoParaJson = buffer.str();
    archivo.close();
    _ConfiguracionItems = nlohmann::json::parse(contenidoParaJson);

    sf::Texture _texturaItems;
    if (!_texturaItems.loadFromFile("ItemsSprites.png")){
        std::cout << "Error al cargar ItemsSprites.png" << std::endl;
    }
}

/*FabricaItems::FabricaItems( sf::Texture& texturaItems, nlohmann::json& ConfiguracionItems){
    _texturaItems = &texturaItems;
    _ConfiguracionItems = &ConfiguracionItems;
}*/

std::unique_ptr<Item> FabricaItems::crearItem(int id){
    if (id == -1) return nullptr;
    auto nuevoItem = std::make_unique<Item>(_texturaItems, id);
    nuevoItem -> setTitulo(_ConfiguracionItems[id]["titulo"].get<std::string>());
    nuevoItem -> setDescripcion(_ConfiguracionItems[id]["descripcion"].get<std::string>());
    nuevoItem -> setCantidadMax(_ConfiguracionItems[id]["cantidad_maxima"].get<int>());
    return nuevoItem;

}
