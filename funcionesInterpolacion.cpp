#include "funcionesInterpolacion.h"
#include <math.h>
using namespace std;

void lerp(sf::Vector2f& valorActual, const sf::Vector2f& objetivo, const float& factorInterpolacion){
    valorActual.x = valorActual.x + ((objetivo.x - valorActual.x)*factorInterpolacion);
    valorActual.y = valorActual.y + ((objetivo.y - valorActual.y)*factorInterpolacion);
}

void lerp(float& valorActual, const float& objetivo, const float& factorInterpolacion){
    valorActual = valorActual + ((objetivo - valorActual)*factorInterpolacion);
}

