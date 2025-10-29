#include <iostream>
using namespace std;
#include "Game.h"
#include "InventarioIntefaz.h"
#include "InventarioResumidoInterfaz.h"
#include "Estructura.h"




Game::Game()
    : window(sf::VideoMode(1024, 768), "SFML works!"), personaTest(300,300)
{
    window.setFramerateLimit(75);
}

void Game::run()
{
    vector<Estructura> vectorEstructuras;

///         inventario  ////


    InventarioInterfaz inv;
    inv.agregarItem(44,30);


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
//    Enemigo VectEnemy[10];

    ///MUSICA
    sf::SoundBuffer buffer;
    sf::Sound sonido;
    if (!buffer.loadFromFile("music.wav"))
    {
        return;
    }

    sonido.setBuffer(buffer);
    sonido.play();
    sonido.setVolume(5.0);
    sonido.setLoop(true);

/// ESTRUCTURA TEST

    vectorEstructuras.push_back(Estructura(45,50));
    vectorEstructuras.push_back(Estructura(70,50));
    vectorEstructuras.push_back(Estructura(80,50));
    vectorEstructuras.push_back(Estructura(10,50));

    while (window.isOpen())
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

        window.clear(sf::Color::Black);
        window.draw(mapa);

        ///

        ///
        mouse.update(window);

        window.setView(Camara);

        character.cmd();


        sf::Vector2f PosicionJugador = character.getPosition();

        ///Mostramos la vida del jugador

//        cout << character.getVida() << endl;


/////////
//        for (int i = 0 ; i < 3 ; i++) {
//
//            VectEnemy[i].Update(PosicionJugador);
//
//            character.chocar(VectEnemy[i].getColisionador());
//
//            float empujeX = 0.f;
//            float empujeY = 0.f;
//            float fuerzaEmpuje = 5.f;
//
//            if (character.getColisionador().detectorDeColision(VectEnemy[i].getColisionador(), empujeX, empujeY)) {
//
////                if (VectEnemy[i].getColisionador().getID()== "Enemy") {
////                    character.move(empujeX * fuerzaEmpuje, empujeY * fuerzaEmpuje);
////                }
//            }
//
//            VectEnemy[i].getColisionador().draw(window);
//            window.draw(VectEnemy[i]);
//        }


/////// COLISIONES



        for (auto& colisionador : mapa._colisiones)
        {
            character.chocar(colisionador);
        }


        for (int i = 0; i < vectorEstructuras.size(); ++i)
        {
            vectorEstructuras[i].actualizarTextura();
            if(!vectorEstructuras[i].estaDestruido())
            {
                if(character.getColisionador().detectorDeColision(vectorEstructuras[i].getColisionador())) ///EJEMPLO
                {
                    character.chocar(vectorEstructuras[i].getColisionador());
                    vectorEstructuras[i].recibirGolpe(5);
                }
                window.draw(vectorEstructuras[i]);
            }
            else
            {
                vectorEstructuras.erase(vectorEstructuras.begin() + i);
            }
        }


///////////
        character.update();
        character.updateEspada(mouse);
/// DRAW


        character.getColisionador().draw(window);

        window.draw(character);

        window.draw(inv);
        float relacion = (float)window.getSize().x/(float)window.getSize().y;
        inv.update(mouse.getPosicion(),mause,Camara,relacion);

        camaraPosicion.x = camaraPosicion.x + ((character.getPosition().x - camaraPosicion.x) * 0.05f );
        camaraPosicion.y = camaraPosicion.y + ((character.getPosition().y- camaraPosicion.y) * 0.05f );

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
