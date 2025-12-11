#include <iostream>
#include "FabricaCultivos.h"
using namespace std;

FabricaCultivos::FabricaCultivos() {
    if (!_texturaCultivos.loadFromFile("Cultivos.png")) {
        std::cout << "Error texture cultivos" << std::endl;
    }
}

std::unique_ptr<cultivo> FabricaCultivos::crearDesdeSemilla(int idItemSemilla, float x, float y) {

    int filaSprite = 0;
    int idProducto = 0;

    ///TRIGO
    if (idItemSemilla == 31) {
        filaSprite = 0;
        idProducto = 37;
    }

    ///PAPA
    else if (idItemSemilla == 33) {
        filaSprite = 1;
        idProducto = 41;
    }

    ///ZANAHORIA
    else if (idItemSemilla == 32) {
        filaSprite = 2;
        idProducto = 38;
    }
    else {
        return nullptr;
    }

    // Creamos el cultivo pas ndole toda la info
    return std::make_unique<cultivo>(_texturaCultivos, x, y, filaSprite, idProducto, idItemSemilla);
}
