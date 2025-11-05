#include <iostream>
using namespace std;
#include "Game.h"


Game::Game()
    : window(sf::VideoMode(1024, 768), "SFML works!"), personaTest(300,300) {
    window.setFramerateLimit(75);
}

void Game::run() {
    ///     TEXTURAS    ////


    // vector<Estructura> vectorEstructuras;
    list <Estructura> listaEstructuras;

    Loot l1({60,50},20,5);



///RELOJ INTERNO/////

    float deltatime;




///         inventario  ////


    InventarioInterfaz inv;
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
    sf::Vector2f empuje;
    empuje.x = 0.f;
    empuje.y = 0.f;
    float fuerzaEmpuje = 50.f;



    std::list<std::unique_ptr<Mob>> enemigos;
    std::list<std::unique_ptr<Mob>> animales;

//    enemigos.push_back(_FabricaMobs.crearMobs("Fantasma", {100 , 100}));
//    enemigos.push_back(_FabricaMobs.crearMobs("Murcielago", {50 , 50}));

    sf::Vector2f _posicionAleatoria;

    _posicionAleatoria.x = (float)(rand()%400);
    _posicionAleatoria.y = (float)(rand()%400);

    for (int i = 0 ; i < 5 ; i++)
    {
        animales.push_back(_FabricaMobs.crearMobs("Vaca", _posicionAleatoria));
        animales.push_back(_FabricaMobs.crearMobs("Oveja", _posicionAleatoria));
        animales.push_back(_FabricaMobs.crearMobs("Cerdo", _posicionAleatoria));
    }



//    Fantasma miFantasma(texturaFantasma , {100 , 100});
//    Murcielago miMurcielago (texturaMurcielago , {50 , 50});

    ///MUSICA
    sf::SoundBuffer buffer;
    sf::Sound sonido;
    if (!buffer.loadFromFile("music.wav")) {
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

    //Se suele usar List no vector
    //Convendria que la textura fuera puntero + llamar a dispose antes de erase()

    /*for(auto& p:listaEstructuras){
        p.actualizarTextura();
    }*/

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
             }
            inv.controlAbrirCerrarInventario(event);
        }

        window.clear(sf::Color::Black);
        window.draw(mapa);

        /// RELOJ

        deltatime = _relojInterno.restart().asMilliseconds();

//        sf::Vector2f uwu (rand()%1000 , rand()%1000);
//
//        enemigos.push_back(_FabricaMobs.crearMobs("Fantasma", {uwu.x , uwu.y}));

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

for (auto& enemigo: enemigos){

    enemigo->update(PosicionJugador, deltatime);

    character.chocar(enemigo->_colision);

    if(character.getColisionador().detectorDeColision(enemigo->_colision, empuje.x, empuje.y))
    {
        character.move(empuje.x * fuerzaEmpuje, empuje.y * fuerzaEmpuje);
    }

}

for (auto& animal: animales){

    animal->update(PosicionJugador, deltatime);

    character.chocar(animal->_colision);
}

for (auto& colisionador : mapa._colisiones) {
    character.chocar(colisionador);
}

for (auto it = listaEstructuras.begin(); it != listaEstructuras.end(); ) {
    if (!it->estaDestruido()) {
        if(character.getColisionador().detectorDeColision(it->getColisionador())) { ///EJEMPLO
            character.chocar(it->getColisionador());
            it->recibirGolpe(5);
        }
        window.draw(*it);
    } else {
        it = listaEstructuras.erase(it);
    }
    it++;
}

/////////// UPDATE
        character.update();
        character.updateEspada(mouse);
//        miFantasma.fantasmaUpdate(PosicionJugador, deltatime);
//        miMurcielago.murcielagoUpdate(PosicionJugador, deltatime);

/// DRAW


        character.getColisionador().draw(window);

        l1.update();

        window.draw(l1);

        window.draw(character);

        for(auto& enemigo : enemigos)
        {
            window.draw(*enemigo);
        }

        for(auto& animal : animales)
        {
            window.draw(*animal);
        }




//        window.draw(miFantasma);
//        window.draw(miMurcielago);

        window.draw(inv);
        float relacion = (float)window.getSize().x/(float)window.getSize().y;
        inv.update(mouse.getPosicion(),mause,Camara,relacion);

        camaraPosicion.x = camaraPosicion.x + ((character.getPosition().x - camaraPosicion.x) * 0.05f );
        camaraPosicion.y = camaraPosicion.y + ((character.getPosition().y- camaraPosicion.y) * 0.05f );

        if (character.getEstaCorriendo()) Camara.setSize(Camara.getSize().x + (350 - Camara.getSize().x)*0.05, Camara.getSize().y + (350 - Camara.getSize().y)*0.05);
        else Camara.setSize(Camara.getSize().x + (300 - Camara.getSize().x)*0.05, Camara.getSize().y + (300 - Camara.getSize().y)*0.05);

        Camara.setCenter(camaraPosicion);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
            guardar(character);
            cout << "Guardado Exitosamente!!" << endl;
        }

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
-objeto loot
-hacer los mobs

-relacion
    -> inventario
    -> estructura
    -> loot

*/
