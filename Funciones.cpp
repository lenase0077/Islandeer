#include <iostream>
#include "Funciones.h"
using namespace std;
#include <cmath>

void setFrame(int fila , int columna, sf::Sprite& sprite){

    sprite.setTextureRect((sf::IntRect(columna * 16 , fila * 16 , 16 , 16)));

}

void setFramePersonaje(int fila , int columna, sf::Sprite& sprite){

    sprite.setTextureRect((sf::IntRect(columna * 32 , fila * 32 , 32 , 32)));

}

float calcularDistancia(const sf::Vector2f& pos1, const sf::Vector2f& pos2)
{
    float difX = pos1.x - pos2.x;
    float difY = pos1.y - pos2.y;

    return sqrt((difX * difX) + (difY * difY));
}

