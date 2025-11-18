#include "TileMap.h" // Asegurate que coincida con tu nombre de archivo (tilemap.h vs TileMap.h)
#include <fstream>
#include <iostream>

using json = nlohmann::json;

bool TileMap::loadFromJSON(const std::string& filename,
                           const std::string& tilesetSuelo,
                           const std::string& tilesetObjetos) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error al abrir el JSON: " << filename << std::endl;
        return false;
    }

    json j;
    file >> j;

    _width = j["width"];
    _height = j["height"];
    _tileWidth = j["tilewidth"];
    _tileHeight = j["tileheight"];

    if (!_texturaSuelo.loadFromFile(tilesetSuelo)) return false;
    if (!_texturaObjetos.loadFromFile(tilesetObjetos)) return false;

    _verticesSuelo.setPrimitiveType(sf::Quads);
    _verticesObjetos.setPrimitiveType(sf::Quads);
    _verticesSuelo.resize(_width * _height * 4);
    _verticesObjetos.resize(_width * _height * 4);

    // --- CORRECCIÓN 1: Inicializar todo como transparente ---
    // Esto evita que los tiles vacíos se dibujen en (0,0)
    for (size_t i = 0; i < _verticesSuelo.getVertexCount(); ++i) {
        _verticesSuelo[i].color = sf::Color::Transparent;
        _verticesObjetos[i].color = sf::Color::Transparent;
    }
    // -------------------------------------------------------

    // 🔹 OBTENER FIRSTGID DE LOS TILESETS
    std::vector<int> firstGIDs;
    for (const auto& tileset : j["tilesets"]) {
        firstGIDs.push_back(tileset["firstgid"]);
    }

    auto& capas = j["layers"];
    int capaIndex = 0;

    for (auto& capa : capas) {
        if (capa["type"] != "tilelayer") continue;

        const std::vector<int> data = capa["data"];
        sf::VertexArray* vertices = (capaIndex == 0) ? &_verticesSuelo : &_verticesObjetos;
        const sf::Texture* textura = (capaIndex == 0) ? &_texturaSuelo : &_texturaObjetos;

        int firstGID = (capaIndex == 0) ? firstGIDs[0] : firstGIDs[1];

        int tilesPerRow = textura->getSize().x / _tileWidth;

        for (int y = 0; y < _height; ++y) {
            for (int x = 0; x < _width; ++x) {
                int gid = data[y * _width + x];

                // Si es 0, ya es transparente por la inicialización, así que 'continue' está bien ahora
                if (gid == 0) continue;

                // 🔹 CALCULAR LOCALID CORRECTAMENTE
                int localID = gid - firstGID;
                if (localID < 0) {
                    continue;
                }

                int tu = localID % tilesPerRow;
                int tv = localID / tilesPerRow;

                sf::Vertex* quad = &(*vertices)[(x + y * _width) * 4];

                // --- CORRECCIÓN 2: Hacer visible el tile válido ---
                // Como los inicializamos transparentes, ahora hay que ponerlos blancos (visibles)
                for (int i = 0; i < 4; i++) {
                    quad[i].color = sf::Color::White;
                }
                // -------------------------------------------------

                quad[0].position = sf::Vector2f(x * _tileWidth, y * _tileHeight);
                quad[1].position = sf::Vector2f((x + 1) * _tileWidth, y * _tileHeight);
                quad[2].position = sf::Vector2f((x + 1) * _tileWidth, (y + 1) * _tileHeight);
                quad[3].position = sf::Vector2f(x * _tileWidth, (y + 1) * _tileHeight);

                quad[0].texCoords = sf::Vector2f(tu * _tileWidth, tv * _tileHeight);
                quad[1].texCoords = sf::Vector2f((tu + 1) * _tileWidth, tv * _tileHeight);
                quad[2].texCoords = sf::Vector2f((tu + 1) * _tileWidth, (tv + 1) * _tileHeight);
                quad[3].texCoords = sf::Vector2f(tu * _tileWidth, (tv + 1) * _tileHeight);

                // 🔹 COLISIONES
                if (capaIndex == 1 && localID >= 0) {
                    // Nota: Cuidado con hardcodear IDs como 1154, pueden cambiar si editas el tileset
                    switch(gid) {
                    case 1154: {
                        Colisionador colision;
                        sf::FloatRect tamanioColision(
                            x * _tileWidth, y * _tileHeight, _tileWidth, _tileHeight);
                        colision.setColision(tamanioColision);
                        _colisiones.push_back(colision);
                        break;
                    }
                    }
                }
            }
        }

        capaIndex++;
        if (capaIndex > 1) break;
    }

    return true;
}
