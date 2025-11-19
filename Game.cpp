#include <iostream>
using namespace std;
#include "Game.h"

Game::Game()
    : window(sf::VideoMode(1024, 768), "SFML works!"),
    _personaje(_texturaPersonaje),
    personaTest(_texturaPersonaje, 300,300),
    _minimap({150.f, 150.f},
{
    1024.f - 160.f, 10.f
})
{
    window.setFramerateLimit(75);
    srand(time(NULL));
}

void Game::run()
{
/// ======================== Texturas =========================///

    // vector<Estructura> vectorEstructuras;
    list <Estructura> listaEstructuras;

    list <Loot> listaLoots;

    sf::Texture texturaItems;
    if (!texturaItems.loadFromFile("ItemsSprites.png"))
    {
        cout << "Error al cargar ItemsSprites.png" << endl;
    }

    if (!_texturaPersonaje.loadFromFile("Basic Charakter Spritesheet.png")) {
        std::cout << "Error cargando textura" << std::endl;
    }

/// ======================== Reloj Externo =========================///

    float deltatime;

/// ======================== Inventario =========================///

    InventarioInterfaz inv(texturaItems);
    inv.agregarItem(44,30);
    inv.agregarItem(15,3);

/// ======================== Mapa =========================///

    mapa.loadFromJSON("mapa.json", "Sprite-0003.png", "UtilidadMapa.png");
    _minimap.build(mapa);

/// ======================== Mouse =========================///
    Raton mouse;
    sf::Mouse mause;

/// ======================== Camara =========================///
    sf::View Camara;
    Camara.setSize({300.f, 300.f});
    sf::Vector2f camaraPosicion = {640, 1120};

/// ======================== Personaje =========================///
    Personaje character (_texturaPersonaje);
    cargar(character);

/// ======================== Enemigo =========================///
    sf::Vector2f empuje;
    empuje.x = 0.f;
    empuje.y = 0.f;
    float fuerzaEmpuje = 50.f;

    std::list<std::unique_ptr<Mob>> enemigos;
    std::list<std::unique_ptr<Mob>> animales;

//    enemigos.push_back(_FabricaMobs.crearMobs("Fantasma", {100 , 100}));
//    enemigos.push_back(_FabricaMobs.crearMobs("Murcielago", {50 , 50}));

/// ======================== Aniamles =========================///

    float spawnX = 82*32;
    float spawnY = 90*32;

    sf::Vector2f _posicionAleatoria;

    for (int i = 0 ; i < 5 ; i++)
    {
        _posicionAleatoria.x = spawnX + (rand()%400 - 200);
        _posicionAleatoria.y = spawnY + (rand()%400 - 200);

        animales.push_back(_FabricaMobs.crearMobs("Vaca", {_posicionAleatoria.x , _posicionAleatoria.y}));
        animales.push_back(_FabricaMobs.crearMobs("Oveja",{_posicionAleatoria.x + 50 ,_posicionAleatoria.y}));
        animales.push_back(_FabricaMobs.crearMobs("Cerdo",{_posicionAleatoria.x - 50 ,_posicionAleatoria.y + 50}));
    }

/// ======================== Musica =========================///
    sf::SoundBuffer buffer;
    sf::Sound sonido;
    if (!buffer.loadFromFile("music.wav"))
    {
        return;
    }

    sonido.setBuffer(buffer);
    sonido.setVolume(_menuPrincipal.getVolumen());
    sonido.setLoop(true);

/// ======================== Estructura =========================///

    listaEstructuras.emplace_back(spawnX + 100, spawnY - 100);
    listaEstructuras.emplace_back(spawnX + 200, spawnY - 50);
    listaEstructuras.emplace_back(spawnX - 100, spawnY - 100);

    listaLoots.emplace_back(texturaItems,sf::Vector2f(spawnX + 99,spawnY - 105),7);
    listaLoots.emplace_back(texturaItems,sf::Vector2f(spawnX + 105,spawnY - 105),8);
    listaLoots.emplace_back(texturaItems,sf::Vector2f(spawnX + 120,spawnY - 100),9);
    listaLoots.emplace_back(texturaItems,sf::Vector2f(spawnX + 150,spawnY - 50),10);
    listaLoots.emplace_back(texturaItems,sf::Vector2f(spawnX + 125,spawnY - 200),11);
    listaLoots.emplace_back(texturaItems,sf::Vector2f(spawnX + 150,spawnY - 100),12);

    //Se suele usar List no vector
    //Convendria que la textura fuera puntero + llamar a dispose antes de erase()

    for(auto& p:listaEstructuras)
    {
        p.actualizarTextura();
    }


/// ======================== CICLO DIA Y NOCHE =========================///
    nightOverlay.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    nightOverlay.setPosition(0.f, 0.f);
    sf::Color nightColor(0, 0, 30); // Un azul oscuro para la noche
    float cicloCompletoSegundos = 30.0f; // Un ciclo de 2 minutos para probar. ¡Puedes cambiar esto!
    sf::Uint8 maxOpacidad = 210; // Qué tan oscura será la noche (0-255)


/// ======================== Fuente y Display Reloj =========================///

        if (!fontReloj.loadFromFile("PIXEARG_.TTF"))
        {
            cout << "Error al cargar la fuente" << endl;
        }

        textReloj.setFont(fontReloj);
        textReloj.setCharacterSize(14);
        textReloj.setFillColor(sf::Color::White);

        textReloj.setPosition(864, 162);


/// ======================== INICIO GAME LOOP =========================///
    while (window.isOpen())
    {
        cout << "Energia = " << character.getEnergia() << endl;
/// ======================== INICIO MENU PRINCIPAL =========================///

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

            _menuPrincipal.ajustarEscalaAutomaticamente(window.getDefaultView());


            OpcionMenu opcion = _menuPrincipal.actualizar(posMouse);

            if (opcion == OpcionMenu::Jugar)
            {
                _estadoActual = EstadoJuego::Jugando;
                sonido.setVolume(_menuPrincipal.getVolumen());
                sonido.play();
                _menuPrincipal.actualizar(posMouse);
                relojDiaNoche.restart();
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
/// ======================== INICIO JUEGO =========================///

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

/// ======================== Primeros drawables =========================///

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



/// ======================== RELOJ =========================///

            deltatime = _relojInterno.restart().asMilliseconds();


            mouse.update(window);

/// ======================== Update del Ciclo dia y noche =========================///

            float tiempoActualSegundos = relojDiaNoche.getElapsedTime().asSeconds();
            float tiempoEnCiclo = fmod(tiempoActualSegundos, cicloCompletoSegundos);

            float fraccionCiclo = (tiempoEnCiclo / cicloCompletoSegundos) * 2.0f * 3.14159265f;
            float opacidad_normalizada = (cos(fraccionCiclo) + 1.0f) / 2.0f;

            sf::Uint8 opacidadActual = static_cast<sf::Uint8>(opacidad_normalizada * maxOpacidad);
            nightOverlay.setFillColor(sf::Color(nightColor.r, nightColor.g, nightColor.b, opacidadActual));

            float fraccionDia = tiempoEnCiclo / cicloCompletoSegundos;
            int totalMinutosJuego = static_cast<int>(fraccionDia * 1440);
            int hora = totalMinutosJuego / 60;
            int minuto = totalMinutosJuego % 60;

            std::stringstream ss;
            ss << std::setw(2) << std::setfill('0') << hora << ":"
               << std::setw(2) << std::setfill('0') << minuto;
            textReloj.setString(ss.str());

/// ======================== COMANDOS =========================///

            character.cmd(deltatime);
            sf::Vector2f PosicionJugador = character.getPosition();

            ///Mostramos la vida del jugador

//        cout << character.getVida() << endl;



/// ======================== COLISION ENEMIGOS =========================///

            for (auto& enemigo: enemigos)
            {

                enemigo->update(PosicionJugador, deltatime);

                character.chocar(enemigo->_colision);

                if(character.getColisionador().detectorDeColision(enemigo->_colision, empuje.x, empuje.y))
                {
                    character.move(empuje.x * fuerzaEmpuje, empuje.y * fuerzaEmpuje);
                }
            }

/// ======================== COLISIONES ANIMAL =========================///

            for (auto it = animales.begin(); it != animales.end();)
            {
                Mob* animal = it->get();

                animal->update(PosicionJugador, deltatime);

                for (auto& colisionadorMapa : mapa._colisiones)
                {
                    animal->chocar(colisionadorMapa);
                }

                bool murio = character.atacar(*animal, fuerzaEmpuje , deltatime);

                if (murio)
                {
                    it = animales.erase(it);
                }

                else
                {
                    animal->move(animal->getVelocidad());
                    ++it;
                }

            }
/// ======================== COLISION MAPA =========================///



            for (auto& colisionador : mapa._colisiones)
            {
                character.chocar(colisionador);
            }



/// ======================== COLISION ESTRUCTURA =========================///

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
                    it++;
                }
                else
                {
                    it->liberarLoot(texturaItems,listaLoots);
                    it = listaEstructuras.erase(it);
                }
            }

            for (auto it = listaLoots.begin(); it != listaLoots.end(); )
            {
                it->update(character.getPosition(),inv);
                window.draw(*it);

                if (it->getLooted())
                {
                    it = listaLoots.erase(it);
                }

                else
                {
                    it++;
                }
            }

/// ======================== INICIO UPDATE =========================///

            character.update();
            character.updateEspada(mouse);
            _minimap.update(character.getPosition());

/// ======================== INICIO DRAWABLES =========================///
            window.setView(window.getDefaultView());

            window.draw(nightOverlay);

            window.draw(_minimap);

            window.draw(textReloj);

/// ======================== CAMARA EFECTO Y CENTRADO =========================///

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
