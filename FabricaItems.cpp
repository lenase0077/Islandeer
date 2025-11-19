#include "FabricaItems.h"
#include <fstream>
#include <iostream>
#include <sstream>

// Constructor - inicializa la fábrica cargando configuraciones
FabricaItems::FabricaItems(){
    ///CARGA DE JSON DE ITEMS ===========================================
    std::ifstream archivo("ItemsConfiguraciones.json");
    // Convertir ifstream a string para el parser JSON
    std::stringstream buffer;
    buffer << archivo.rdbuf();
    std::string contenidoParaJson = buffer.str();
    archivo.close();
    _ConfiguracionItems = nlohmann::json::parse(contenidoParaJson); // Parsea JSON

    // CORRECCIÓN: Quitar "sf::Texture" - usar directamente el miembro de clase
    // Carga el atlas de sprites de todos los items
    if (!_texturaItems.loadFromFile("ItemsSprites.png")){
        std::cout << "Error al cargar ItemsSprites.png" << std::endl;
    }
}

// Método factory - crea items según ID con configuraciones predefinidas
std::unique_ptr<Item> FabricaItems::crearItem(int id){
    //if (id == -1) return nullptr; // (Comentado) Podría manejar ID inválido

    // Crea nuevo item con textura e ID
    auto nuevoItem = std::make_unique<Item>(_texturaItems, id);

    // Configura propiedades desde JSON
    nuevoItem -> setTitulo(_ConfiguracionItems[id]["titulo"].get<std::string>());
    nuevoItem -> setDescripcion(_ConfiguracionItems[id]["descripcion"].get<std::string>());
    nuevoItem -> setCantidadMax(_ConfiguracionItems[id]["cantidad_maxima"].get<int>());

    return nuevoItem; // Devuelve item completamente configurado
}
