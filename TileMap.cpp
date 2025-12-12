#include "tilemap.h"
#include <fstream>
using json = nlohmann::json;


#include <iostream>







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

    // 🔹 OBTENER FIRSTGID DE LOS TILESETS
    std::vector<int> firstGIDs;
    for (const auto& tileset : j["tilesets"]) {
        firstGIDs.push_back(tileset["firstgid"]);
    }

    // Primer tileset: firstGID = 1 (suelo)
    // Segundo tileset: firstGID = 33 (objetos)

    auto& capas = j["layers"];
    int capaIndex = 0;



    for (auto& capa : capas) {
        if (capa["type"] != "tilelayer") continue;

        const std::vector<int> data = capa["data"];

        if (capaIndex == 0) {
            _idsSuelo = data; // Guardamos todo el array de IDs
        }

        sf::VertexArray* vertices = (capaIndex == 0) ? &_verticesSuelo : &_verticesObjetos;
        const sf::Texture* textura = (capaIndex == 0) ? &_texturaSuelo : &_texturaObjetos;

        int firstGID = (capaIndex == 0) ? firstGIDs[0] : firstGIDs[1]; // Suelo usa tileset 0, objetos usa tileset 1

        int tilesPerRow = textura->getSize().x / _tileWidth;



        for (int y = 0; y < _height; ++y) {
            for (int x = 0; x < _width; ++x) {
                int gid = data[y * _width + x];
                if (gid == 0) continue;

                // 🔹 CALCULAR LOCALID CORRECTAMENTE
                int localID = gid - firstGID;
                if (localID < 0) {
                    // El tile no pertenece a este tileset, saltar
                    continue;
                }

                int tu = localID % tilesPerRow;
                int tv = localID / tilesPerRow;

                sf::Vertex* quad = &(*vertices)[(x + y * _width) * 4];
                quad[0].position = sf::Vector2f(x * _tileWidth, y * _tileHeight);
                quad[1].position = sf::Vector2f((x + 1) * _tileWidth, y * _tileHeight);
                quad[2].position = sf::Vector2f((x + 1) * _tileWidth, (y + 1) * _tileHeight);
                quad[3].position = sf::Vector2f(x * _tileWidth, (y + 1) * _tileHeight);

                quad[0].texCoords = sf::Vector2f(tu * _tileWidth, tv * _tileHeight);
                quad[1].texCoords = sf::Vector2f((tu + 1) * _tileWidth, tv * _tileHeight);
                quad[2].texCoords = sf::Vector2f((tu + 1) * _tileWidth, (tv + 1) * _tileHeight);
                quad[3].texCoords = sf::Vector2f(tu * _tileWidth, (tv + 1) * _tileHeight);

                // 🔹 COLISIONES - Solo en segunda capa
                if (capaIndex == 1 && localID >= 0) {
                    switch(gid) {
                    case 161:
                    case 321:
                    case 353:
                    case 385:
                    case 257:
                    {
                        Colisionador colision;
                        sf::FloatRect tamanioColision(
                            x * _tileWidth, y * _tileHeight, _tileWidth, _tileHeight);
                        colision.setColision(tamanioColision);
                        _colisiones.push_back(colision);
                        break;
                    }
                    case 258:
                    {
                        Colisionador colision;
                        sf::FloatRect tamanioColision(
                            x * _tileWidth, y * _tileHeight, _tileWidth, _tileHeight);
                        colision.setColision(tamanioColision);
                        _colisiones.push_back(colision);
                        break;
                    }
                    case 289:
                    {
                        Colisionador colision;
                        sf::FloatRect tamanioColision(
                            x * _tileWidth, y * _tileHeight, _tileWidth / 2, _tileHeight);
                        colision.setColision(tamanioColision);
                        _colisiones.push_back(colision);
                        break;
                    }
                    case 290:
                    {
                        Colisionador colision;
                        sf::FloatRect tamanioColision(
                            (x * _tileWidth) + _tileWidth / 2, y * _tileHeight, _tileWidth / 2, _tileHeight);
                        colision.setColision(tamanioColision);
                        _colisiones.push_back(colision);
                        break;
                    }
                    case 291:
                    {
                        Colisionador colision;
                        sf::FloatRect tamanioColision(
                            x * _tileWidth,  (y *_tileHeight) + _tileHeight / 2 , _tileWidth, _tileHeight /2);
                        colision.setColision(tamanioColision);
                        _colisiones.push_back(colision);
                        break;
                    }
                    }
                }
            }
        }

        capaIndex++;
        if (capaIndex > 1) break; // sólo suelo y objetos
    }

    return true;
}


int TileMap::getTileID(int x, int y) const
{

    if (x >= 0 && x < _width && y >= 0 && y < _height) {
            return _idsSuelo[y * _width + x];
        }
        return 0;
}
