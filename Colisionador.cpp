#include <iostream>
using namespace std;
#include "Colisionador.h"
#include <cmath>

Colisionador::Colisionador(){

}

Colisionador::Colisionador(string ID){
    _ID = ID;
}

void Colisionador::setID (string ID){
    _ID = ID;
}

void Colisionador::setColision(sf::FloatRect colision)
{
    _colision = colision;
}

std::string Colisionador::getID (){
    return _ID;
}

sf::FloatRect Colisionador::getColision()
{
    return _colision;
}

bool Colisionador::detectorDeColision(Colisionador& colisionado) const {

    if (_colision.intersects(colisionado.getColision())) {
//        cout << colisionado.getID() << endl;
        return true;
    }
    return false;
}

bool Colisionador::detectorDeColision( Colisionador& colisionado , float& empujeX , float& empujeY) const{

    if (!_colision.intersects(colisionado.getColision())){
        empujeX = 0.f;
        empujeY = 0.f;
        return false;
    }

    ///Ubicamos el centro del personaje
    float centroX1 = _colision.left + _colision.width / 2.0f;
    float centroY1 = _colision.top + _colision.height / 2.0f;

    ///Ubicamos el centro del enemigo
    float centroX2 = colisionado.getColision().left + colisionado.getColision().width / 2.0f;
    float centroY2 = colisionado.getColision().top + colisionado.getColision().height / 2.0f;

    ///Calculo Vector de empuje -> Para que el personaje se desplace en la direcci¢n opuesta al enemigo
    empujeX = centroX1 - centroX2;
    empujeY = centroY1 - centroY2;

    ///Normalizamos el vector para que la fuerza siempre sea 1.0
    ///La longitud nos mide que tan lejos estan los centros del personaje y del enemigo
    float longitud = std::sqrt(empujeX * empujeX + empujeY * empujeY);
    if (longitud > 0.0f) {
        empujeX /= longitud;
        empujeY /= longitud;
    }

    return true;
}

void Colisionador::draw(sf::RenderWindow& window)
{
    rectanguloDebug.setPosition(_colision.left, _colision.top);
    sf::Vector2f tamano(_colision.width, _colision.height);
    rectanguloDebug.setSize(tamano);
    rectanguloDebug.setFillColor(sf::Color::Transparent);
    rectanguloDebug.setOutlineColor(sf::Color::White);
    rectanguloDebug.setOutlineThickness(1);
    window.draw(rectanguloDebug);
}
