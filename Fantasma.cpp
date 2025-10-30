#include "Fantasma.h"

Fantasma::Fantasma(const sf::Texture& textura)
{

    _colision.setID("Fantasma");
    setTexture(textura);
    setScale(0.8 , 0.8);
    setTextureRect(sf::IntRect(0,0,32,32));
    setVida(100);

}

Fantasma::Fantasma(const sf::Texture& textura , sf::Vector2f PosicionInicial)
{
    _colision.setID("Fantasma");
    setPosition(PosicionInicial);
    setTexture(textura);
    setTextureRect(sf::IntRect(0,0,32,32));
    setVida(100);
}

void Fantasma::fantasmaUpdate(sf::Vector2f& Posicionpersonaje)
{
    updateColision();

    if (perseguir(Posicionpersonaje, 1.f))
    {
        setFrame(0,0);
    }
    else{
        setFrame(0,1);
    }

    perseguir(Posicionpersonaje, 1.f);
    move(getVelocidad());

}
