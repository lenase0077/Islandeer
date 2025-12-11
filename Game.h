#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Personaje.h"
#include "TileMap.h"
#include "Enemigo.h"
#include "InventarioIntefaz.h"
#include "Comando.h"
#include "InventarioResumidoInterfaz.h"
#include "Estructura.h"
#include "Loot.h"
#include "Fantasma.h"
#include "Murcielago.h"
#include <list>
#include "FabricaMobs.h"
#include <memory>
#include <ctime>
#include "Minimap.h"
#include "Menu_Principal.h"
#include "EstadodeJuego.h"
#include "FabricaEstructuras.h"
#include "FabricaItems.h"
#include <fstream>
#include <set>
#include <cmath>

class Game
{
    public:
        Game();
        void run();
        void guardar(Personaje &character);
        void cargar (Personaje &character);
        sf::Clock getRelojInterno();

    private:


        sf::Texture _texturaPersonaje;
        Personaje _personaje;
        sf::RenderWindow window;
        sf::Vector2f _posicionPersonaje;
        sf::Clock _relojInterno;
        FabricaMobs _FabricaMobs;
        FabricaEstructuras _FabricaEstructuras;
        Minimap _minimap;
        TileMap mapa;
        float _tiempoDiaAcumulado = 0;
        sf::View Camara;


        //==== DIA Y NOCHE===//
        sf::Clock relojDiaNoche;
        sf::RectangleShape nightOverlay;
        float cicloCompletoSegundos;
        sf::Uint8 maxOpacidad;

        sf::Font fontReloj;
        sf::Text textReloj;

        EstadoJuego _estadoActual = EstadoJuego::MenuPrincipal;
        MenuPrincipal _menuPrincipal;

        void regenerarRecursos(std::list<std::unique_ptr<Estructura>>& listaEstructurasAleatorias);

/// --- VARIABLES DE USO PARA FADE IN Y FADE OUT TEST

        sf::RectangleShape _fadeRect;   // El rectangulo negro
        float _fadeAlpha = 0.0f;        // Transparencia actual
        bool _enTransicion = false;
        int _estadoFade = 0;            // 0: Nada, 1: Oscureciendo, 2: Aclarando
        sf::Vector2f _destinoTeleport;  // Guardamos a donde queremos ir

        void actualizarFade(Personaje& character);
        void iniciarTeletransporte(float x, float y);
        void verificarTeleports(Personaje& character);


};
