#include "FabricaEstructuras.h"
#include <iostream>
using namespace std;

FabricaEstructuras::FabricaEstructuras(){
    if(!_texturaEstructuras.loadFromFile("Bloques.png")) {
        cout << "Error cargando textura" << endl;
    }
}
void FabricaEstructuras::update(){
    ///EN PROSCESO
    /*for (auto it = listaEstructuras.begin(); it != listaEstructuras.end(); ) {
            if (!it->estaDestruido()) {
                if(character.getColisionador().detectorDeColision(it->getColisionador())) { ///EJEMPLO
                    character.chocar(it->getColisionador());
                    it->recibirGolpe(5);
                }
                window.draw(*it);
            }
            else
            {
                it->liberarLoot(texturaItems,listaLoots);
                it = listaEstructuras.erase(it);
            }
            it++;
    }*/
}
void FabricaEstructuras::crearEstructura(float x, float y, int ID){
    _listaEstructuras.emplace_back(_texturaEstructuras,x,y,ID);
}
