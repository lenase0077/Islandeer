#include <iostream>
using namespace std;
#include "Game.h"


Game::Game()
    : window(sf::VideoMode(1024, 768), "SFML works!"), personaTest(300,300), _minimap({150.f, 150.f},
{
    1024.f - 160.f, 10.f
})
{
    window.setFramerateLimit(75);
    srand(time(NULL));
}


void Game::run()
{
    ///     TEXTURAS    ////


    // vector<Estructura> vectorEstructuras;
    list <Estructura> listaEstructuras;

    list <Loot> listaLoots;

    sf::Texture texturaItems;
    if (!texturaItems.loadFromFile("ItemsSprites.png"))
    {
        cout << "Error al cargar ItemsSprites.png" << endl;
    }


///RELOJ INTERNO/////

    float deltatime;

///         inventario  ////


    InventarioInterfaz inv(texturaItems);
    inv.agregarItem(44,30);
    inv.agregarItem(15,3);


///      MAPA TEST ///

    mapa.loadFromJSON("mapa.json", "Sprite-0003.png", "UtilidadMapa.png");
    _minimap.build(mapa);



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

    std::list<std::unique_ptr<Mob>> enemigos;
    std::list<std::unique_ptr<Mob>> animales;

//    enemigos.push_back(_FabricaMobs.crearMobs("Fantasma", {100 , 100}));
//    enemigos.push_back(_FabricaMobs.crearMobs("Murcielago", {50 , 50}));

    ///ANIMALES
    sf::Vector2f _posicionAleatoria;

    for (int i = 0 ; i < 5 ; i++)
    {
        _posicionAleatoria.x = (float)(rand()%400);
        _posicionAleatoria.y = (float)(rand()%400);

        animales.push_back(_FabricaMobs.crearMobs("Vaca", {84*32,90*32}));
        animales.push_back(_FabricaMobs.crearMobs("Oveja", {80*32,95*32}));
        animales.push_back(_FabricaMobs.crearMobs("Cerdo", {90*32,85*32}));
    }

    ///MUSICA
    sf::SoundBuffer buffer;
    sf::Sound sonido;
    if (!buffer.loadFromFile("music.wav"))
    {
        return;
    }

    sonido.setBuffer(buffer);
    sonido.play();
    sonido.setVolume(100.0);
    sonido.setLoop(true);

/// ESTRUCTURA TEST

    listaEstructuras.emplace_back(70,50);
    listaEstructuras.emplace_back(80,60);
    listaEstructuras.emplace_back(10,50);

    listaLoots.emplace_back(texturaItems,sf::Vector2f(99,105),7);
    listaLoots.emplace_back(texturaItems,sf::Vector2f(105,105),8);
    listaLoots.emplace_back(texturaItems,sf::Vector2f(120,100),9);
    listaLoots.emplace_back(texturaItems,sf::Vector2f(150,50),10);
    listaLoots.emplace_back(texturaItems,sf::Vector2f(125,200),11);
    listaLoots.emplace_back(texturaItems,sf::Vector2f(150,100),12);

    //Se suele usar List no vector
    //Convendria que la textura fuera puntero + llamar a dispose antes de erase()

    for(auto& p:listaEstructuras)
    {
        p.actualizarTextura();
    }

    while (window.isOpen())
    {

        switch(_estadoActual)
        {

        case EstadoJuego::MenuPrincipal:
        {

            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            Comandos::getInstancia().actualizar();
            sf::Vector2f posMouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

            OpcionMenu opcion = _menuPrincipal.actualizar(posMouse);

            if (opcion == OpcionMenu::Jugar)
            {
                _estadoActual = EstadoJuego::Jugando;
                _menuPrincipal.actualizar(posMouse);


            }
            else if (opcion == OpcionMenu::Salir)
            {
                window.close();
            }

            window.clear(sf::Color::Black);
            window.setView(window.getDefaultView());
            window.draw(_menuPrincipal);
            window.display();
            break;
        }

        case EstadoJuego::Jugando:
        {

            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }

                inv.controlAbrirCerrarInventario(event);
            }




            Comandos::getInstancia().actualizar();
            sf::Vector2f posMouseAux = window.mapPixelToCoords(sf::Mouse::getPosition(window));









            ///DRAWABLES

            window.clear(sf::Color::Black);

            window.setView(Camara);
            window.draw(mapa);
            window.draw(character);






            character.getColisionador().draw(window);



            for(auto& enemigo : enemigos)
            {
                window.draw(*enemigo);
            }

            for(auto& animal : animales)
            {
                window.draw(*animal);
            }

            window.draw(inv);



            /// RELOJ

            deltatime = _relojInterno.restart().asMilliseconds();


            mouse.update(window);


/// CHARACTER COMANDOS

            character.cmd();
            sf::Vector2f PosicionJugador = character.getPosition();

            ///Mostramos la vida del jugador

//        cout << character.getVida() << endl;



/////// COLISIONES

            for (auto& enemigo: enemigos)
            {

                enemigo->update(PosicionJugador, deltatime);

                character.chocar(enemigo->_colision);

                if(character.getColisionador().detectorDeColision(enemigo->_colision, empuje.x, empuje.y))
                {
                    character.move(empuje.x * fuerzaEmpuje, empuje.y * fuerzaEmpuje);
                }
            }

            //========

            for (auto& animal: animales)
            {

                animal->update(PosicionJugador, deltatime);

                character.chocar(animal->_colision);

                for (auto& colisionadorMapa : mapa._colisiones)
                {
                    animal->chocar(colisionadorMapa);
                }

                if(character.getColisionador().detectorDeColision(animal->_colision, empuje.x, empuje.y))
                {
                    animal->move(-empuje.x * fuerzaEmpuje, -empuje.y * fuerzaEmpuje);
                    character.move(empuje.x * fuerzaEmpuje, empuje.y * fuerzaEmpuje);
                }

                animal->move(animal->getVelocidad());
            }
            //==========

            for (auto& colisionador : mapa._colisiones)
            {
                character.chocar(colisionador);
            }

            for (auto it = listaEstructuras.begin(); it != listaEstructuras.end(); )
            {
                if (!it->estaDestruido())
                {
                    if(character.getColisionador().detectorDeColision(it->getColisionador()))   ///EJEMPLO
                    {
                        character.chocar(it->getColisionador());
                        it->recibirGolpe(5);
                    }
                    window.draw(*it);
                }
                else
                {
                    it->liberarLoot(texturaItems,listaLoots);
                    it = listaEstructuras.erase(it);
                }
                it++;
            }


            for (auto it = listaLoots.begin(); it != listaLoots.end(); )
            {
                it->update(character.getPosition(),inv);
                window.draw(*it);
                if (it->getLooted()) it = listaLoots.erase(it);
                it++;
            }

/////////// UPDATE
            character.update();
            character.updateEspada(mouse);

            _minimap.update(character.getPosition());

/// MINIMAPA UPDATE


/// DRAW
            window.setView(window.getDefaultView());
            window.draw(_minimap);





            float relacion = (float)window.getSize().x/(float)window.getSize().y;
            inv.update(mouse.getPosicion(),mause,Camara,relacion);

            camaraPosicion.x = camaraPosicion.x + ((character.getPosition().x - camaraPosicion.x) * 0.1f );
            camaraPosicion.y = camaraPosicion.y + ((character.getPosition().y- camaraPosicion.y) * 0.1f );

            if (character.getEstaCorriendo()) Camara.setSize(Camara.getSize().x + (350 - Camara.getSize().x)*0.05, Camara.getSize().y + (350 - Camara.getSize().y)*0.05);
            else Camara.setSize(Camara.getSize().x + (300 - Camara.getSize().x)*0.05, Camara.getSize().y + (300 - Camara.getSize().y)*0.05);

            Camara.setCenter(camaraPosicion);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
            {
                guardar(character);
                cout << "Guardado Exitosamente!!" << endl;
            }

            window.display();

        }


        }


    }
}

void Game::guardar(Personaje &character)
{
    FILE *Puntero = fopen("ultimoGuardado", "wb");
    if (Puntero== nullptr)
    {
        cout << "ERROR 404" << endl;
    }

    _posicionPersonaje = character.getPosition();

    fwrite(&_posicionPersonaje, sizeof(_posicionPersonaje),1,Puntero);

    fclose(Puntero);
}

void Game::cargar(Personaje &character)
{

    FILE *Puntero = fopen("ultimoGuardado", "rb");
    if (Puntero== nullptr)
    {
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
-objeto loot
-hacer los mobs

-relacion
    -> inventario
    -> estructura
    -> loot

*/
