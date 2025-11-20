#include "Estructura.h"
#include <iostream>
#include <cmath>

using namespace std;


Estructura::Estructura(sf::Texture& texturaBloques, float posX, float posY, int id)
{
    _sprite.setTexture(texturaBloques);

    ///Acomodamos su sprite en base a su ID
    int columnasTextura = 7;
    int alturaFrame = 32;
    int anchuraFrame = 32;

    int frameX = anchuraFrame * (id % columnasTextura);
    int frameY = alturaFrame * (id / columnasTextura);

    _sprite.setTextureRect(sf::IntRect(frameX,frameY,anchuraFrame,alturaFrame));

    setPosition(posX,posY);

    sf::FloatRect colisionadorDimenciones(posX + 8,posY + 8,16,16);

    _colision.setColision(colisionadorDimenciones);
    _colision.setID("Estructura");
}

void Estructura::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(_sprite, states);
/// Mover a Arbol
//    if (_tieneCopa) {
//        target.draw(_spriteCopa, states);
//    }
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

void Estructura::setVida(float nuevaVida){
    _vida = nuevaVida;
}

///Esto hay que cambiarlo por un creador de loot para darle un control mas optimo.
void Estructura::liberarLoot(FabricaItems& fabItems,list<Loot>& listaLoot){
    int distanciaLoots = 8;
    const float PI = 3.1415926535f;
    float lootPosX, lootPosY;
    int iterador = 0;
    for (auto& p : _lootsIDs ) {
        float anguloGrados = (360.0f / _lootsIDs.size()) * iterador;
        float anguloRadianes = anguloGrados * (PI / 180.0f);

        lootPosX = getPosition().x + 16 +(cos(anguloRadianes)* distanciaLoots);
        lootPosY = getPosition().y + 16 +(sin(anguloRadianes)* distanciaLoots);
        listaLoot.emplace_back(fabItems,sf::Vector2f(lootPosX,lootPosY), p);
        iterador++;
    }
}

void Estructura::setLootsIDs(const std::vector<int>& nuevoLootsIDs){
    _lootsIDs = nuevoLootsIDs;
}

void Estructura::update(const sf::Vector2f& posicionJugador, const sf::Vector2f& posGlobalDelMouse, const sf::Mouse& mouse, const sf::View& vista, const float& relacionAspecto, InventarioInterfaz& inventario){

}

//void Estructura::setCopa(const sf::Texture& texturaCopa, int idFrameCopa) {
//    _tieneCopa = true;
//    _spriteCopa.setTexture(texturaCopa);
//
//    // Calculamos el frame igual que hiciste en el constructor
//    int columnasTextura = 7; // O las que tenga tu png de copas
//    int tamanoAlto = 64;    // 32x32
//    int tamanoAncho = 32;    // 32x32
//
//    int frameX = tamanoAlto * (idFrameCopa % columnasTextura);
//    int frameY = tamanoAncho * (idFrameCopa / columnasTextura);
//
//    _spriteCopa.setTextureRect(sf::IntRect(frameX, frameY, tamanoAncho, tamanoAlto));
//    // LA CLAVE: Posicionamos la copa relativa al tronco (0, -32)
//
//    _spriteCopa.setPosition(0.f, -64.f);
//}



