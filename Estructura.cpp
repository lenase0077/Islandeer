#include "Estructura.h"
#include <iostream>
using namespace std;


Estructura::Estructura( float posX, float posY)
    : _vida(100.f) {

    actualizarTextura();

    _sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
    _sprite.setPosition(posX, posY);

    _colision.setColision(_sprite.getGlobalBounds());
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
    listaLoot.emplace_front(texturaItems,sf::Vector2f(_sprite.getPosition().x+4,_sprite.getPosition().y), ID);
    listaLoot.emplace_front(texturaItems,sf::Vector2f(_sprite.getPosition().x,_sprite.getPosition().y), ID);
    listaLoot.emplace_front(texturaItems,sf::Vector2f(_sprite.getPosition().x-4,_sprite.getPosition().y), ID);
}

//
//
//    void update();

