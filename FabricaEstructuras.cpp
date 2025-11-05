#include "FabricaEstructuras.h"
#include <iostream>
#include <memory>
using namespace std;

FabricaEstructuras::FabricaEstructuras(){
    if(!_texturaEstructuras.loadFromFile("Bloques.png")) {
        cout << "Error cargando textura" << endl;
    }
}
void FabricaEstructuras::update(){

}
//return std::make_unique<Murcielago>(_murcielagoTexture, posicion);
std::unique_ptr<Estructura> FabricaEstructuras::crearEstructura(float x, float y, int ID){
    //_listaEstructuras.emplace_back(_texturaEstructuras,x,y,ID);
    auto estructuraCreada = std::make_unique<Estructura>(_texturaEstructuras, x, y, ID);
    std::vector<int> vectorLootIDs;
    switch(ID){
    case 0:
        estructuraCreada -> setVida(100);
        for (int i = 0; i < (1+rand() % 3); i++){
           vectorLootIDs.push_back(1);
        }
        estructuraCreada -> setLootsIDs(vectorLootIDs);
        break;
    case 1:
        estructuraCreada -> setVida(200);
        break;
    case 2:
        estructuraCreada -> setVida(300);
        break;
    }

    return estructuraCreada;
}
