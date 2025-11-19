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

std::unique_ptr<Estructura> FabricaEstructuras::crearEstructura(float x, float y, int ID){
    auto estructuraCreada = std::make_unique<Estructura>(_texturaEstructuras, x, y, ID);
    std::vector<int> vectorLootIDs;
    switch(ID){
    case 0:///Tronco
        estructuraCreada -> setVida(100);

        insertarLootEntre(10,vectorLootIDs,2,5);
        estructuraCreada -> setLootsIDs(vectorLootIDs);
        break;
    case 1:///Piedra
        estructuraCreada -> setVida(200);

        insertarLootEntre(18,vectorLootIDs,2,8);
        estructuraCreada -> setLootsIDs(vectorLootIDs);
        break;
    case 2:///Piedra + Carbon
        estructuraCreada -> setVida(300);

        insertarLootEntre(18,vectorLootIDs,0,2);
        insertarLootEntre(19,vectorLootIDs,2,8);
        estructuraCreada -> setLootsIDs(vectorLootIDs);
        break;
    case 3:///Piedra + Hierro
        estructuraCreada -> setVida(300);

        insertarLootEntre(18,vectorLootIDs,0,2);
        insertarLootEntre(11,vectorLootIDs,2,8);
        estructuraCreada -> setLootsIDs(vectorLootIDs);
        break;
    case 4:///Piedra + Oro
        estructuraCreada -> setVida(300);

        insertarLootEntre(18,vectorLootIDs,0,2);
        insertarLootEntre(12,vectorLootIDs,2,8);
        estructuraCreada -> setLootsIDs(vectorLootIDs);
        break;
    case 5:///Piedra + Diamante
        estructuraCreada -> setVida(400);

        insertarLootEntre(18,vectorLootIDs,0,2);
        insertarLootEntre(22,vectorLootIDs,1,3);
        estructuraCreada -> setLootsIDs(vectorLootIDs);
        break;
    case 6:///Piedra + obsidiana
        estructuraCreada -> setVida(800);

        insertarLootEntre(18,vectorLootIDs,0,2);
        insertarLootEntre(23,vectorLootIDs,1,3);
        estructuraCreada -> setLootsIDs(vectorLootIDs);
        break;
    case 7:///mesa de crafteo
        estructuraCreada = std::make_unique<MesaDeCrafteo>(_texturaEstructuras, x, y, ID);
        estructuraCreada -> setVida(100);
        vectorLootIDs.push_back(52);
        estructuraCreada -> setLootsIDs(vectorLootIDs);
        break;
    }
    return estructuraCreada;
}

void FabricaEstructuras::insertarLootEntre(int ID, std::vector<int>& vectorLootsIDs, int minimo, int maximo){
    for (int i = 0; i < (minimo + rand() % (maximo-minimo + 1)); i++){
           vectorLootsIDs.push_back(ID);
    }
}
