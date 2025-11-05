#include "Murcielago.h"

Murcielago::Murcielago(const sf::Texture& textura)
{
    _colision.setID("Murcielago");
    setTexture(textura);
    setScale(0.8 , 0.8);
    setTextureRect(sf::IntRect(0,0,32,32));
    setVida(100);
}

Murcielago::Murcielago(const sf::Texture& textura , sf::Vector2f PosicionInicial)
{
    _colision.setID("Murcielago");
    setPosition(PosicionInicial);
    setTexture(textura);
    setTextureRect(sf::IntRect(0,0,32,32));
    setVida(100);
}

void Murcielago::murcielagoUpdate(sf::Vector2f& Posicionpersonaje, float deltatime)
{
    updateColision();
    Animar(deltatime);
    comportamiento(Posicionpersonaje, 1.f,deltatime);
    move(getVelocidad());
}

void Murcielago::Animar(float deltaTime)
{

    _tiempoDeAnimar += deltaTime;

    if (_tiempoDeAnimar >= 80)
    {

        if (_frameActual >= 5)
        {
            _frameActual = 0;
        }
        else
        {
             _frameActual++;
        }

        setFrame(0, _frameActual);

        _tiempoDeAnimar -= 80;

    }
}
