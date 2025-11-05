#include "Fantasma.h"


Fantasma::Fantasma(const sf::Texture& textura)
{


    _colision.setID("Fantasma");


    setTexture(textura);

    setTextureRect(sf::IntRect(0,0,32,32));

    setVida(100);



}

Fantasma::Fantasma(const sf::Texture& textura, sf::Vector2f posicionInicial)
{
    _colision.setID("Fantasma");
    setPosition(posicionInicial);
    setTexture(textura);
    setTextureRect(sf::IntRect(0,0,32,32));
    setVida(100);
}

void Fantasma::fantasmaUpdate(sf::Vector2f& Posicionpersonaje, float deltatime)
{
    updateColision();
    if (perseguir(Posicionpersonaje, 1.f)){
        setFrame(0,1);
    }
    else
    {
        divagar(Posicionpersonaje, 1.f, deltatime);
        setFrame(0,0);
    }
    move(getVelocidad());
}

void Fantasma::update(sf::Vector2f& Posicionpersonaje, float deltatime)
{
    fantasmaUpdate(Posicionpersonaje, deltatime);
}
