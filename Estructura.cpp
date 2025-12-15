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

    float centradoX = 6.0f;
    float centradoY = 6.0f;

    sf::FloatRect colisionadorDimenciones(posX + centradoX ,posY + centradoY,20,20);

    _colision.setColision(colisionadorDimenciones);
    _colision.setID("Estructura");

    _seRompePorColision = true;

    _bloqueID = id;

    if (id == 0 || (id >= 10 && id <= 12) || id == 7 || id == 8 || id == 13) {
        _material = TipoMaterial::MADERA;
    }
    else if ((id >= 1 && id <= 6) || id == 9) {
        _material = TipoMaterial::PIEDRA;
    }
    else {
        _material = TipoMaterial::NADA;
    }
}

void Estructura::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(_sprite, states);
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
        listaLoot.emplace_back(fabItems,sf::Vector2f(lootPosX,lootPosY), p, 1);
        iterador++;
    }
}

void Estructura::setLootsIDs(const std::vector<int>& nuevoLootsIDs){
    _lootsIDs = nuevoLootsIDs;
}

void Estructura::update(const sf::Vector2f& posicionJugador, const sf::Vector2f& posGlobalDelMouse, const sf::View& vista, const float& relacionAspecto, InventarioInterfaz& inventario, InventarioInterfaz& inventarioCofre, float deltatime){

}


void Estructura::generarLoot (std::list<Loot>& listaLoot){

}

bool Estructura::getRompePorColision()
{
    return _seRompePorColision;
}

int Estructura::getID(){
    return _bloqueID;
}

bool Estructura::estaEnUso(){
    return _enUso;
}

