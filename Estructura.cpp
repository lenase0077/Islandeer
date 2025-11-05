#include "Estructura.h"
#include <iostream>
#include <cmath>
using namespace std;


Estructura::Estructura( float posX, float posY)
    : _vida(100.f) {

    actualizarTextura();

    _sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
    setPosition(posX,posY);

    sf::FloatRect colisionadorDimenciones(posX + 8,posY + 8,16,16);

    _colision.setColision(colisionadorDimenciones);
    _colision.setID("Estructura");

}

void Estructura::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(_sprite, states);
}



void Estructura::actualizarTextura() {
    if (!_textura.loadFromFile("Bloques.png")) {
        std::cout << "Error cargando textura" << std::endl;
    }
    _sprite.setTexture(_textura);

}


void Estructura::recibirGolpe(float danio) {
    _vida -= danio;
    if (_vida < 0.0f) {
        _vida = 0.0f;
    }
}

bool Estructura::estaDestruido() const {
    return _vida <= 0.0f;
}

///Esto hay que cambiarlo por un creador de loot para darle un control mas optimo.
void Estructura::liberarLoot(sf::Texture& texturaItems,list<Loot>& listaLoot){
    int ID = 10;
    int cantidadLoots = 180;
    int distanciaLoots = 8;
    float lootPosX, lootPosY;
    for (int n = 0; n < cantidadLoots; n++){
        lootPosX = getPosition().x + 16 +(cos((360/cantidadLoots)*n) * distanciaLoots);
        lootPosY = getPosition().y + 16 +(sin((360/cantidadLoots)*n) * distanciaLoots);
        listaLoot.emplace_front(texturaItems,sf::Vector2f(lootPosX,lootPosY), ID);
    }
}



