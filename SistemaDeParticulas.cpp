#include "SistemaDeParticulas.h"


SistemaParticulas::SistemaParticulas()
{
    _forma.setRadius(3.f);
    _forma.setOrigin(3.f, 3.f);
}

void SistemaParticulas::emitirVeneno(sf::Vector2f posOrigen)
{
    for (int i = 0; i < 15; i++)
    {
        Particula p; // Instanciamos la clase Particula
        p.posicion = posOrigen;

        float velX = (rand() % 40 - 20) * 1.5f;
        float velY = (rand() % 30 + 20) * -1.5f;

        p.velocidad = sf::Vector2f(velX, velY);
        p.vidaMax = (rand() % 10 + 5) / 10.0f;
        p.vida = p.vidaMax;

        p.color = sf::Color(50, 200 + (rand()%55), 50);

        _particulas.push_back(p);
    }
}

void SistemaParticulas::update(float dt)
{
    float segundos = dt / 1000.0f;

    for (auto it = _particulas.begin(); it != _particulas.end(); )
    {
        it->posicion += it->velocidad * segundos;
        it->vida -= segundos;

        if (it->vida <= 0)
        {
            it = _particulas.erase(it);
        }
        else
        {
            it++;
        }
    }
}

void SistemaParticulas::draw(sf::RenderWindow& window)
{
    for (const auto& p : _particulas)
    {
        _forma.setPosition(p.posicion);

        float ratio = p.vida / p.vidaMax;
        sf::Color c = p.color;
        c.a = static_cast<sf::Uint8>(255 * ratio);

        _forma.setFillColor(c);
        window.draw(_forma);
    }
}

void SistemaParticulas::emitirBrilloDorado(sf::Vector2f posOrigen)
{
    for (int i = 0; i < 3; i++)
    {
        Particula p;
        p.posicion = posOrigen;

        float angulo = (rand() % 360) * 3.14159f / 180.f;
        float velocidad = (rand() % 60 + 30); // Velocidad rápida

        p.velocidad = sf::Vector2f(cos(angulo) * velocidad, sin(angulo) * velocidad);

        p.vidaMax = (rand() % 5 + 5) / 10.0f; // Viven poco (0.5 a 1.0 seg)
        p.vida = p.vidaMax;

        p.color = sf::Color(255, 200 + (rand()%55), 0);

        _particulas.push_back(p);
    }
}
