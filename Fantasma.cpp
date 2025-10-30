#include "Fantasma.h"


Fantasma::Fantasma(const sf::Texture& textura)
{


    _colision.setID("Fantasma");


    setTexture(textura);

    setTextureRect(sf::IntRect(0,0,32,32));

    setVida(100);



}

void Fantasma::fantasmaUpdate(sf::Vector2f& Posicionpersonaje)
{
    updateColision();
    perseguir(Posicionpersonaje, 1.f);
    move(getVelocidad());
}
