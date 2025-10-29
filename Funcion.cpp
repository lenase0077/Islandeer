using namespace std;
#include "Funcion.h"
#include <iostream>

void setFrame (int columna, int fila, sf::Sprite& sprite)
{


    sprite.setTextureRect((sf::IntRect(columna * 16, fila * 16, 16, 16)));
}


