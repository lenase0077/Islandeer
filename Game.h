#pragma once
#include <SFML/Graphics.hpp>
#include "Personaje.h"
#include "TileMap.h"
#include "Enemigo.h"

class Game
{
    public:
        Game();
        void run();
        void guardar(Personaje &character);
        void cargar (Personaje &character);

    private:
        Personaje _personaje;
        Personaje personaTest;
        sf::RenderWindow window;
        sf::Vector2f _posicion;
};
