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

void Fantasma::fantasmaUpdate(sf::Vector2f& Posicionpersonaje , float deltaTime)
{
    updateColision();

    if (comportamiento(Posicionpersonaje, 1.f , deltaTime))
    {
        setFrame(0,0);
    }
    else
    {
        setFrame(0,1);
    }

    comportamiento(Posicionpersonaje, 1.f , deltaTime);
    move(getVelocidad());

}
