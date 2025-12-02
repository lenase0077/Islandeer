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

    cargarDatosHerramientas();
}

TipoMaterial FabricaItems::stringAEnum(std::string s) {
    if (s == "MADERA") return TipoMaterial::MADERA;
    if (s == "PIEDRA") return TipoMaterial::PIEDRA;
    if (s == "HIERRO") return TipoMaterial::HIERRO;
    if (s == "DIAMANTE") return TipoMaterial::DIAMANTE;

    if (s == "CARNE") return TipoMaterial::CARNE;
    return TipoMaterial::NADA;
}

void FabricaItems::cargarDatosHerramientas() {
    std::ifstream archivo("herramientas.json");
    if (!archivo.is_open()) return;

    nlohmann::json j;
    archivo >> j;

    for (auto& itemJson : j) { // Recorre cada herramienta del JSON
        DatosHerramienta datos;
        int id = itemJson["id"];
        datos.durabilidad = itemJson["durabilidad"];
        datos.danioBase = itemJson["danio_base"];

        if (itemJson.contains("multiplicadores")) {
            for (auto& el : itemJson["multiplicadores"].items()) {
                // Convierte string "PIEDRA" a enum TipoMaterial::PIEDRA Esta en ITEM.H gil
                TipoMaterial mat = stringAEnum(el.key());
                datos.multiplicadores[mat] = el.value();
            }
        }
        // Guardamos en el mapa de la fábrica
        _datosHerramientas[id] = datos;
    }
}


// Método factory - crea items según ID con configuraciones predefinidas
std::unique_ptr<Item> FabricaItems::crearItem(int id){
    //if (id == -1) return nullptr; // (Comentado) Podría manejar ID inválido

    if (_datosHerramientas.count(id)) {
        DatosHerramienta& d = _datosHerramientas[id];

        auto herramienta = std::make_unique<Herramienta>(_texturaItems, id, d.durabilidad, d.danioBase);

        for (auto const& [mat, val] : d.multiplicadores) {
            herramienta->agregarMultiplicador(mat, val);
        }

        if (_ConfiguracionItems.contains(std::to_string(id))) {
            herramienta->setTitulo(_ConfiguracionItems[id]["titulo"]);
            herramienta -> setDescripcion(_ConfiguracionItems[id]["descripcion"].get<std::string>());
            herramienta -> setCantidadMax(_ConfiguracionItems[id]["cantidad_maxima"].get<int>());
        }

        return herramienta;
    }


    // Crea nuevo item con textura e ID
    auto nuevoItem = std::make_unique<Item>(_texturaItems, id);

    // Configura propiedades desde JSON
    nuevoItem -> setTitulo(_ConfiguracionItems[id]["titulo"].get<std::string>());
    nuevoItem -> setDescripcion(_ConfiguracionItems[id]["descripcion"].get<std::string>());
    nuevoItem -> setCantidadMax(_ConfiguracionItems[id]["cantidad_maxima"].get<int>());

    return nuevoItem; // Devuelve item completamente configurado
}
