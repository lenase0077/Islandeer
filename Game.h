#pragma once
#include "Cultivos.h"
#include "FabricaCultivos.h"
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
#include "InterfazEstado.h"
#include "TextoFlotante.h"
#include "SistemaDeParticulas.h"
#include "BarcoHuida.h"
#include "InterfazBarcoHuida.h"
#include "SelectorDeOpciones.h"


class Game
{
    public:
        Game();
        void run();
        void guardarPartida();
        void cargarPartida();
        sf::Clock getRelojInterno();
        sf::Texture _texturaCultivos;
        std::list<std::unique_ptr<cultivo>> _listaCultivos;
        std::list <std::unique_ptr<Estructura>> _listaEstructuras;
        void updateCultivos(float deltatime);
        void intentarPlantar(sf::Vector2f posMouseWorld, InventarioInterfaz& inv);
        void intentarCosecharClick(sf::Vector2f posMouseWorld, std::list<Loot>& listaLoots, FabricaItems& fabItems);
        bool esSueloCultivable(int tileID);

        ///refactorizacion para mejor lectura
        void procesarAtaqueEstructura(Estructura* estructura, const sf::FloatRect& rectEspada, InventarioInterfaz& inv);

        void usarItemEnMano(Personaje& character, InventarioInterfaz& inv);

        void mostrarTexto (std::string mensaje, float x, float y);
        void mostrarTexto (std::string mensaje, float x, float y, float duracion);
        void colocarEstructura(sf::Vector2f posMouseWorld, InventarioInterfaz& inv, std::list<std::unique_ptr<Estructura>>& lista);


        FabricaItems fabItems;
        InventarioInterfaz inv;

        std::unique_ptr<BarcoHuida> barco;
        std::unique_ptr<InterfazBarcoHuida> interfazBarco;
        std::unique_ptr<SelectorDeOpciones> opcionesBarcoHuida;

        sf::Texture texturaBarcoHuida;
        sf::Texture texturaInterfazBarcoHuida;
        sf::Texture texturaBotonesInterfazBarco;
        sf::Font fuentePixelArt;





    private:
        sf::Text _textoFPS;
        float _tiempoFPS = 0.0f;
        InterfazEstado _interfazEstado;
        std::list<std::unique_ptr<TextoFlotante>> _listaTextos;

        sf::SoundBuffer _bufferComer;
        sf::Sound _sonidoComer;

        sf::Texture _texturaPersonaje;
        Personaje character;
        sf::RenderWindow window;
        sf::Vector2f _posicionPersonaje;
        sf::Clock _relojInterno;
        FabricaMobs _FabricaMobs;
        FabricaCultivos _fabricaCultivos;

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
        void regenerarAnimales(std::list<std::unique_ptr<Mob>>& listaAnimalesAleatorias);

/// --- VARIABLES DE USO PARA FADE IN Y FADE OUT TEST

        bool _transicionMenuJugando = false;

        sf::RectangleShape _fadeRect;   // El rectangulo negro
        float _fadeAlpha = 0.0f;        // Transparencia actual
        bool _enTransicion = false;
        int _estadoFade = 0;            // 0: Nada, 1: Oscureciendo, 2: Aclarando
        sf::Vector2f _destinoTeleport;  // Guardamos a donde queremos ir

        void actualizarFade(Personaje& character);
        void iniciarTeletransporte(float x, float y);
        void verificarTeleports(Personaje& character);

        SistemaParticulas _particulas;


};
