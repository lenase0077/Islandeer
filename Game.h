#pragma once
#include <SFML/Graphics.hpp>
#include "Personaje.h"
#include "TileMap.h"
#include "Enemigo.h"
#include "InventarioIntefaz.h"
#include "InventarioResumidoInterfaz.h"
#include "Estructura.h"
#include "Loot.h"
#include "Fantasma.h"
#include "Murcielago.h"
#include <list>
#include "FabricaEnemigos.h"
#include <memory>
#include <ctime>


class Game
{
    public:
        Game();
        void run();
        void guardar(Personaje &character);
        void cargar (Personaje &character);
        sf::Clock getRelojInterno();

    private:
        Personaje _personaje;
        Personaje personaTest;
        sf::RenderWindow window;
        sf::Vector2f _posicionPersonaje;
        sf::Clock _relojInterno;
        FabricaEnemigos _FabricaEnemigos;
};
