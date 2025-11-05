#include <iostream>
using namespace std;
#include "Game.h"
#include "InventarioIntefaz.h"
#include "InventarioResumidoInterfaz.h"
#include "Estructura.h"
#include "Loot.h"
#include <list>

Game::Game()
    : window(sf::VideoMode(1024, 768), "SFML works!"), personaTest(300,300)
{
    window.setFramerateLimit(75);
}

void Game::run()
{
    ///


    list <Estructura> listaEstructuras;
    list <Loot> listaLoots;

    sf::Texture texturaItems;
    if (!texturaItems.loadFromFile("ItemsSprites.png")){
        cout << "Error al cargar ItemsSprites.png" << endl;
    }

///         inventario  ////


    InventarioInterfaz inv(texturaItems);
    inv.agregarItem(44,30);
    inv.agregarItem(15,3);


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

    for(auto& p:listaEstructuras){
        p.actualizarTextura();
    }

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

        for (auto it = listaEstructuras.begin(); it != listaEstructuras.end(); )
        {
            if (!it->estaDestruido()){
                if(character.getColisionador().detectorDeColision(it->getColisionador())) ///EJEMPLO
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


        for (auto it = listaLoots.begin(); it != listaLoots.end(); ){
            it->update(character.getPosition(),inv);
            window.draw(*it);
            if (it->getLooted()) it = listaLoots.erase(it);
            it++;
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
