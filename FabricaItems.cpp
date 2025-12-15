#include "FabricaItems.h"
#include <fstream>
#include <iostream>
#include <sstream>


// Constructor - inicializa la fabrica cargando configuraciones
FabricaItems::FabricaItems(){
    ///CARGA DE JSON DE ITEMS ===========================================
    std::ifstream archivo("ItemsConfiguraciones.json");
    if (archivo.is_open()) {
        std::stringstream buffer;
        buffer << archivo.rdbuf();
        std::string contenidoParaJson = buffer.str();
        archivo.close();

        // 1. Leemos el archivo como un Array (Lista) temporal
        nlohmann::json jsonArray = nlohmann::json::parse(contenidoParaJson);

        // 2. CONVERSIÓN AUTOMÁTICA: De Array a Mapa
        // Inicializamos la variable de la clase como un Objeto vacío
        _ConfiguracionItems = nlohmann::json::object();

        // Recorremos la lista y re-guardamos cada item usando su ID como "Clave"
        for (auto& item : jsonArray) {
            if (item.contains("id")) {
                int id = item["id"];
                std::string idStr = std::to_string(id);

                // Aquí ocurre la magia: Guardamos en memoria: "0": {datos...}
                _ConfiguracionItems[idStr] = item;
            }
        }
    } else {
        std::cout << "No se pudo abrir ItemsConfiguraciones.json" << std::endl;
        _ConfiguracionItems = nlohmann::json::object(); // Evita crash si no hay archivo
    }

    // Carga el atlas de sprites
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
        // Guardamos en el mapa de la f�brica
        _datosHerramientas[id] = datos;
    }
}


std::unique_ptr<Item> FabricaItems::crearItem(int id)
{
    // 1. CONVERTIR ID A STRING (La clave del éxito)
    // Como ahora _ConfiguracionItems es un Mapa, la llave es "0", "1", etc.
    std::string idStr = std::to_string(id);

    // ========================================================
    // CASO A: ES UNA HERRAMIENTA (Existe en herramientas.json)
    // ========================================================


    bool esPico(id == 0 || id == 1 || id == 2 );
    bool esHacha(id == 3 || id == 4 || id == 5 );
    bool esEspada(id == 6 || id == 7 || id == 8 );


    if (_datosHerramientas.count(id))
    {
        DatosHerramienta& d = _datosHerramientas[id];
        auto herramienta = std::make_unique<Herramienta>(_texturaItems, id, d.durabilidad, d.danioBase);



        for (auto const& [mat, val] : d.multiplicadores) {
            herramienta->agregarMultiplicador(mat, val);
        }

        if (esHacha) herramienta->setTipoSonido(SonidoHerramienta::HACHA);

        // Cargamos titulo/descripcion si existen en el OTRO json
        // IMPORTANTE: Usamos idStr, NO id
        if (_ConfiguracionItems.contains(idStr))
        {
            herramienta->setTitulo(_ConfiguracionItems[idStr]["titulo"]);
            herramienta->setDescripcion(_ConfiguracionItems[idStr]["descripcion"]);

            if(_ConfiguracionItems[idStr].contains("cantidad_maxima"))
                 herramienta->setCantidadMax(_ConfiguracionItems[idStr]["cantidad_maxima"]);
            else
                 herramienta->setCantidadMax(1);
        }
        else
        {
            herramienta->setTitulo("Herramienta " + idStr);
        }

        return herramienta;
    }

    // ========================================================
    // CASO B: ES UN ITEM NORMAL
    // ========================================================
    auto nuevoItem = std::make_unique<Item>(_texturaItems, id);

    // IMPORTANTE: Usamos idStr, NO id
    if (_ConfiguracionItems.contains(idStr))
    {
        nuevoItem->setTitulo(_ConfiguracionItems[idStr]["titulo"]);
        nuevoItem->setDescripcion(_ConfiguracionItems[idStr]["descripcion"]);

        if(_ConfiguracionItems[idStr].contains("cantidad_maxima"))
             nuevoItem->setCantidadMax(_ConfiguracionItems[idStr]["cantidad_maxima"]);
        else
             nuevoItem->setCantidadMax(64);
    }
    else
    {
        // Fallback si el ID no está en el JSON
        nuevoItem->setTitulo("Item " + idStr);
        nuevoItem->setDescripcion("Sin descripcion");
        nuevoItem->setCantidadMax(64);
    }

    return nuevoItem;
}
// usar esto
