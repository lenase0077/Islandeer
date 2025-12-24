#include <iostream>
#include "Funciones.h"
using namespace std;
#include <cmath>

void setFrame(int fila , int columna, sf::Sprite& sprite){

    sprite.setTextureRect((sf::IntRect(columna * 16 , fila * 16 , 16 , 16)));

}
// usar esto
void setFramePersonaje(int fila , int columna, sf::Sprite& sprite){

    sprite.setTextureRect((sf::IntRect(columna * 32 , fila * 32 , 32 , 32)));
}

float calcularDistancia(const sf::Vector2f& pos1, const sf::Vector2f& pos2)
{
    float difX = pos1.x - pos2.x;
    float difY = pos1.y - pos2.y;

    return sqrt((difX * difX) + (difY * difY));
}

std::string AjustarStringAutomaticamente(std::string stringOriginal, float anchoPixeles, int anchoMax){
    string Lectura = "";
    string desbordePostEspacio = "";
    string stringOutput = stringOriginal;

    ///PONEMOS LOS SALTOS EN EL TEXTO
    int PosicionUltimoEspacio = 0;
    for (int i = 0 ; i < stringOutput.size() ; i++){
        char caracter = stringOutput[i];

        if (caracter == ' '){
            PosicionUltimoEspacio = i;
            desbordePostEspacio = "";
        }

        ///Agregamos caracter por caracter
        Lectura += caracter;
        desbordePostEspacio += caracter;

        ///Si se pasa del ancho maximo -> \n
        if ((Lectura.size() * anchoPixeles) >= anchoMax && caracter!='\n'){
            stringOutput[PosicionUltimoEspacio] = '\n';
            Lectura = desbordePostEspacio;
        }
    }
    return stringOutput;
}
