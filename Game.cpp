#include <iostream>
#include <fstream>
#include "Game.h"
#include "FabricaEstructuras.h"
#include "FabricaItems.h"
#include "json.hpp"
using namespace std;


Game::Game()
    : window(sf::VideoMode(1024, 768), "SFML works!"), personaTest(300,300) {
    window.setFramerateLimit(75);
}


void Game::run() {
///     CARGA DE ARCHIVOS    ////

    sf::Texture texturaFantasma;
    if(!texturaFantasma.loadFromFile("GatoFantasma-Sheet.png")) {
        std::cout << "Error cargando GatoFantasma-Sheet.png" << endl;
    }

    sf::Texture texturaMurcielago;
    if(!texturaMurcielago.loadFromFile("murcielago.png")) {
        std::cout << "Error cargando murcielago.png" << endl;
    }

    list <std::unique_ptr<Estructura>> listaEstructuras;
    list <Loot> listaLoots;


    sf::Texture texturaInventarioResumido;
    if(!texturaInventarioResumido.loadFromFile("InventarioResumido.png")){
        cout << "ERROR AL CARGAR InventarioResumido.png" << endl;
    }

    FabricaEstructuras fabE;

    sf::Keyboard tecladoEntrada;

    //RELOJ INTERNO/////

    float deltatime;
///         inventario  ////



    FabricaItems fabItems;

    InventarioInterfaz inv(fabItems);

    inv.agregarItem(44,30);
    inv.agregarItem(15,3);  //<<<=== falla


    InventarioResumido invR(texturaInventarioResumido);


///      MAPA TEST ///

    TileMap mapa;
    mapa.loadFromJSON("mapa.json", "Sprite-0003.png", "Items.png");


    /// MOUSE
    Raton mouse;
    sf::Mouse mause;

    ///CAMARA
    sf::View Camara;
    Camara.setSize({300.f, 300.f});
    sf::Vector2f camaraPosicion = {640, 1120};

    ///PERSONAJE
    Personaje character;
    cargar(character);

    ///ENEMIGO

    sf::Vector2f empuje;
    empuje.x = 0.f;
    empuje.y = 0.f;
    float fuerzaEmpuje = 50.f;

    Fantasma miFantasma(texturaFantasma , {100 , 100});
    Murcielago miMurcielago (texturaMurcielago , {50 , 50});

    ///MUSICA
    sf::SoundBuffer bufferSonido;
    sf::Sound sonido;
    if (!bufferSonido.loadFromFile("music.wav")) {
        return;
    }

    sonido.setBuffer(bufferSonido);
    sonido.play();
    sonido.setVolume(5.0);
    sonido.setLoop(true);


/// ESTRUCTURA TEST
    listaEstructuras.push_back(fabE.crearEstructura(100,132,0));
    listaEstructuras.push_back(fabE.crearEstructura(132,132,1));
    listaEstructuras.push_back(fabE.crearEstructura(164,132,2));
    listaEstructuras.push_back(fabE.crearEstructura(200,132,3));
    listaEstructuras.push_back(fabE.crearEstructura(232,132,4));
    listaEstructuras.push_back(fabE.crearEstructura(264,132,5));
    listaEstructuras.push_back(fabE.crearEstructura(300,132,6));
    listaEstructuras.push_back(fabE.crearEstructura(332,132,7));


    while (window.isOpen()) {

        cout << "se abrio ventana" << endl;

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            inv.controlDeEventos(event);
            invR.cambiarSlotsConEventos(event);
        }

        window.clear(sf::Color::Black);
        window.draw(mapa);

        /// RELOJ

        deltatime = _relojInterno.restart().asMilliseconds();

        ///
        mouse.update(window);

        window.setView(Camara);

        character.cmd();


        sf::Vector2f PosicionJugador = character.getPosition();

/////// COLISIONES

        character.chocar(miFantasma._colision);

        if (character.getColisionador().detectorDeColision(miFantasma._colision , empuje.x , empuje.y)) {

            if (miFantasma._colision.getID()== "Fantasma") {
                character.move(empuje.x * fuerzaEmpuje, empuje.y * fuerzaEmpuje);
            }
        }

        character.chocar(miMurcielago._colision);

        if (character.getColisionador().detectorDeColision(miMurcielago._colision , empuje.x , empuje.y)) {

            if (miMurcielago._colision.getID()== "Murcielago") {
                character.move(empuje.x * fuerzaEmpuje, empuje.y * fuerzaEmpuje);
            }
        }

        for (auto& colisionador : mapa._colisiones) {
            character.chocar(colisionador);
        }

        float relacion = (float)window.getSize().x/(float)window.getSize().y;

        for (auto estructura = listaEstructuras.begin(); estructura != listaEstructuras.end(); ) {
            if ((*estructura)->estaDestruido() == false) {
                if(character.getColisionador().detectorDeColision((*estructura)->getColisionador())) { ///EJEMPLO
                    character.chocar((*estructura)->getColisionador());
                    (*estructura)->recibirGolpe(5);
                }
                window.draw(**estructura);
                (*estructura)->update( PosicionJugador, mouse.getPosicion(), mause, Camara, relacion, inv);
            }
            else
            {
                (*estructura)->liberarLoot(fabItems,listaLoots);
                estructura = listaEstructuras.erase(estructura);
            }
            estructura++;
        }


        for (auto it = listaLoots.begin(); it != listaLoots.end();){
            it->update(character.getPosition(),inv);
            window.draw(*it);
            if (it->getLooted()) it = listaLoots.erase(it);
            else it++;

        }

/////////// UPDATE
        character.update();
        character.updateEspada(mouse);
        miFantasma.fantasmaUpdate(PosicionJugador, deltatime);
        miMurcielago.murcielagoUpdate(PosicionJugador, deltatime);

/// DRAW

        character.getColisionador().draw(window);

        window.draw(character);
        window.draw(miFantasma);
        window.draw(miMurcielago);
        window.draw(inv);
        inv.update( mouse.getPosicion(), mause, Camara, relacion, listaLoots, tecladoEntrada); ///FALLAA

        camaraPosicion.x = camaraPosicion.x + ((character.getPosition().x - camaraPosicion.x) * 0.1f );
        camaraPosicion.y = camaraPosicion.y + ((character.getPosition().y- camaraPosicion.y) * 0.1f );

        if (character.getEstaCorriendo()) Camara.setSize(Camara.getSize().x + (350 - Camara.getSize().x)*0.05, Camara.getSize().y + (350 - Camara.getSize().y)*0.05);
        else Camara.setSize(Camara.getSize().x + (300 - Camara.getSize().x)*0.05, Camara.getSize().y + (300 - Camara.getSize().y)*0.05);

        Camara.setCenter(camaraPosicion);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)){
            guardar(character);
            cout << "Guardado Exitosamente!!" << endl;
        }
        Item* vectorCarga[30];
        inv.copiarItemsEnVector(vectorCarga);
        invR.setItems(vectorCarga); //<<<FALLAA

        invR.update(Camara, relacion);
        window.draw(invR);
        window.display();

    }
}

void Game::guardar(Personaje &character) {
    FILE *Puntero = fopen("ultimoGuardado", "wb");
    if (Puntero== nullptr) {
        cout << "ERROR 404" << endl;
    }

    _posicionPersonaje = character.getPosition();

    fwrite(&_posicionPersonaje, sizeof(_posicionPersonaje),1,Puntero);

    fclose(Puntero);
}

void Game::cargar(Personaje &character) {

    FILE *Puntero = fopen("ultimoGuardado", "rb");
    if (Puntero== nullptr) {
        cout << "ERROR 404" << endl;
    }

    fread(&_posicionPersonaje, sizeof(_posicionPersonaje),1,Puntero);

    character.setPosicion(_posicionPersonaje.x, _posicionPersonaje.y);

    fclose(Puntero);
}

sf::Clock Game::getRelojInterno()
{
    return _relojInterno;
}


/*

input

terminar:
-objeto loot ######
-hacer los mobs ######
    -mejorar estados de mobs

-relacion
    -> inventario ########
    -> estructura ########
    -> loot       ########

    --> Modificar inventario para que funcione con PUNTEROS DE ITEMS

    -> crear mesa de craftea #### CANCELADO TEMPORALMENTE PARA CAMBIAR MANEJO DE ITEMS
      -> Detecta jugador a cierta distancia ####
      -> Mostrar UI cuando este cerca
      -> Poner Botones y navegar entre la UI


    Fabrica items:
        Comida
            Usar();
        Herramienta
            Usar();
        Estructura
            Usar();

    Buscar item en mano
        Items
            Usar();

    clase comportamiento item:
        Alimento
        Ataque
        Estructura

    Herramienta
        Herramienta(setID) tiene metodo usar();
            Decide que hijo ser:
                    Comida

                    Estructura

                    Ataque

*/
