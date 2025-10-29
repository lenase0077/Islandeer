#include <iostream>
#include "Funciones.h"
using namespace std;

void setFrame(int fila , int columna, sf::Sprite& sprite){

    sprite.setTextureRect((sf::IntRect(columna * 16 , fila * 16 , 16 , 16)));

}
