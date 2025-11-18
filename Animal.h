#pragma once
#include <SFML/Graphics.hpp>
#include "Mob.h"
#include <ctime>

enum class EstadoAnimal{
    Divagando,
    EsReposo,
    Huyendo
};

class Animal : public Mob
{
    public:
        Animal(const sf::Texture& textura);
        Animal(const sf::Texture& textura , sf::Vector2f PosicionInicial);
        void update(sf::Vector2f& Posicionpersonaje, float deltatime);
        void AnimalUpdate(sf::Vector2f& Posicionpersonaje, float deltatime);
        void enReposo (float deltaTime);
        void recibirAtaqueDeEspada();

    private:
        EstadoAnimal _estadoActual;
        float _tiempoEnEstado;
        float _tiempoEnReposo;
        float _tiempoDivagacion;
        void actualizarSpriteAnimacion (float deltaTime);
        bool _golpeadoPorEspada = false;
        void huir(sf::Vector2f& Posicionpersonaje, float aceleracion);
        void actualizarDireccion();
        void recibirDanio();
};
