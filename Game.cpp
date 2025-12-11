#include <iostream>
#include <fstream>
#include "Game.h"
#include "json.hpp"
using namespace std;


Game::Game()
    : window(sf::VideoMode(1024, 768), "SFML works!"),
      _personaje(_texturaPersonaje),
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

    list <std::unique_ptr<Estructura>> listaEstructuras;
    list <Loot> listaLoots;
    list <std::unique_ptr<Estructura>> listaEstructuraRandom;





    sf::Texture texturaInventarioResumido;
    if(!texturaInventarioResumido.loadFromFile("InventarioResumido.png"))
    {
        cout << "ERROR AL CARGAR InventarioResumido.png" << endl;
    }

    if (!_texturaPersonaje.loadFromFile("Personaje.png"))
    {
        std::cout << "Error cargando textura" << std::endl;
    }
    if (!_texturaCultivos.loadFromFile("Cultivos.png"))
    {
        std::cout << "Error cargando textura Cultivos" << std::endl;
    }


/// ======================== Configuracion del FADE  =========================///


    _fadeRect.setSize(sf::Vector2f(2000, 2000)); // Mismo tamaño que tu ventana
    _fadeRect.setFillColor(sf::Color::Black);
    _fadeAlpha = 0.0f;

/// ======================== Reloj Externo =========================///
    FabricaEstructuras fabE;

    sf::Keyboard tecladoEntrada;

    //RELOJ INTERNO/////

    float deltatime;

/// ======================== Inventario =========================///

    FabricaItems fabItems;

    InventarioInterfaz inv(fabItems);
    InventarioInterfaz inventarioCofre(fabItems, "InventarioCofre.png");


    inv.agregarItem(44,30);
    inv.agregarItem(0,1);
    inv.agregarItem(2,1);

    inv.agregarItem(6,1);
    inv.agregarItem(8,1);

    inv.agregarItem(3,1);
    inv.agregarItem(5,1);
    inv.agregarItem(15,3);
    inv.agregarItem(14,10);

    inv.agregarItem(19,20);
    inv.agregarItem(11,1);
    inv.agregarItem(12,1);
//    inv.agregarItem(45,1);
//    inv.agregarItem(47,1);
    inv.agregarItem(28,16);

    InventarioResumido invR(texturaInventarioResumido);

    inv.setInventarioResumido(&invR);

    Item* vectorCarga[30];


/// ======================== Mapa =========================///

    mapa.loadFromJSON("mapa.json", "Sprite-0003.png", "UtilidadMapa.png");
    _minimap.build(mapa);

/// ======================== Mouse =========================///
    Raton mouse;
    sf::Mouse mause;

/// ======================== Camara =========================///
    Camara.setSize({300.f, 300.f});
    sf::Vector2f camaraPosicion = {640, 1120};

/// ======================== Personaje =========================///
    Personaje character (_texturaPersonaje);
    cargar(character);
    float hambrePorSegundo = 0.5f;







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

        animales.push_back(_FabricaMobs.crearMobs("Vaca", {_posicionAleatoria.x, _posicionAleatoria.y}));
        animales.push_back(_FabricaMobs.crearMobs("Oveja", {_posicionAleatoria.x + 50,_posicionAleatoria.y}));
        animales.push_back(_FabricaMobs.crearMobs("Cerdo", {_posicionAleatoria.x - 50,_posicionAleatoria.y + 50}));
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


/// ESTRUCTURA TEST
    listaEstructuras.push_back(fabE.crearEstructura(82*32,85*32,0));
    listaEstructuras.push_back(fabE.crearEstructura(83*32,85*32,1));
    listaEstructuras.push_back(fabE.crearEstructura(84*32,85*32,2));
    listaEstructuras.push_back(fabE.crearEstructura(85*32,85*32,3));
    listaEstructuras.push_back(fabE.crearEstructura(86*32,85*32,4));
    listaEstructuras.push_back(fabE.crearEstructura(87*32,85*32,5));
    listaEstructuras.push_back(fabE.crearEstructura(88*32,85*32,6));
    listaEstructuras.push_back(fabE.crearEstructura(89*32,85*32,7));
    listaEstructuras.push_back(fabE.crearEstructura(89*32,90*32,7));

    listaEstructuras.push_back(fabE.crearEstructura(90*32,85*32,9));

    listaEstructuras.push_back(fabE.crearEstructura(91*32,85*32,8));
    listaEstructuras.push_back(fabE.crearEstructura(91*32,86*32,8));
    listaEstructuras.push_back(fabE.crearEstructura(91*32,90*32,8));
/// ======================== CICLO DIA Y NOCHE =========================///
    nightOverlay.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    nightOverlay.setPosition(0.f, 0.f);
    sf::Color nightColor(0, 0, 30); // Un azul oscuro para la noche
    float cicloCompletoSegundos = 120.0f; // Un ciclo de 2 minutos para probar. CAMBIA ESTO
    sf::Uint8 maxOpacidad = 210; // Que tan oscura es la noche (0-255)

/// ======================== Fuente y Display Reloj =========================///

    if (!fontReloj.loadFromFile("PIXEARG_.TTF"))
    {
        cout << "Error al cargar la fuente" << endl;
    }

    textReloj.setFont(fontReloj);
    textReloj.setCharacterSize(14);
    textReloj.setFillColor(sf::Color::White);
    textReloj.setPosition(864, 162);

    /// ======================== Inicio estructura Random =========================///

    regenerarRecursos(listaEstructuraRandom);

//    character.setPosicion(0, 0);




/// ======================== INICIO GAME LOOP =========================///
    while (window.isOpen())
    {
//        cout << "Energia = " << character.getEnergia() << endl;

/// ======================== INICIO MENU PRINCIPAL =========================///

        switch(_estadoActual)
        {

        case EstadoJuego::MenuPrincipal:
        {
            _menuPrincipal.iniciarMusica();

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
                _menuPrincipal.detenerMusica();
                sonido.setVolume(_menuPrincipal.getVolumen());
                sonido.play();
                _menuPrincipal.actualizar(posMouse);
                _relojInterno.restart();
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

            float volumenActual = _menuPrincipal.getVolumen();
            sonido.setVolume(volumenActual);
            character.setVolumen(volumenActual);
            deltatime = _relojInterno.restart().asMilliseconds();
            Comandos::getInstancia().actualizar();

            _interfazEstado.update( character.getVida(), character.getVidaMaxima(), character.getEnergia(), character.getEnergiaMaxima(), character.getHambre(), character.getHambreMaxima());



            sf::Event event;
            bool cambioDeEstado = false;


            /// ======================== AUXILIAR HERRAMIENTAS =========================///

            bool golpeHabilitado = false;

            if (Comandos::getInstancia().mouseIzqRecienPresionado)
            {
                golpeHabilitado = character.iniciarAtaque();

                if (golpeHabilitado) cout << "Seba gei" << endl;
            }


            while (window.pollEvent(event))
            {
///           ------------- LLAMADA DE EVENTOS -------------
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }

                if (event.type == sf::Event::MouseWheelScrolled)
                {
                    Comandos::getInstancia().registrarScroll(event.mouseWheelScroll.delta);
                }

                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                {
                    _estadoActual = EstadoJuego::MenuPrincipal;
                    sonido.stop();
                    _menuPrincipal.iniciarMusica();
                    cambioDeEstado = true;
                    break;
                }

            }
/// ======================== INICIO DEL GAME LOOP  ======================== ///
            if (cambioDeEstado) break;

            sf::Vector2f posMouseWorld = window.mapPixelToCoords(sf::Mouse::getPosition(window), Camara);

            /// ======================== Test spawn =========================///
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
            {
                static sf::Clock relojPlantar;
                if (relojPlantar.getElapsedTime().asSeconds() > 0.2f)
                {
                    // Solo intentamos plantar
                    intentarPlantar(posMouseWorld, inv);
                    relojPlantar.restart();
                }
            }

            // --- CONTROL CLICK IZQUIERDO (ROMPER CULTIVO)
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                static sf::Clock relojRomper;
                if (relojRomper.getElapsedTime().asSeconds() > 0.2f)
                {
                    // Intentamos romper/cosechar el cultivo
                    intentarCosecharClick(posMouseWorld, listaLoots, fabItems);

                    // Aqu� tambi�n podr�as poner l�gica de atacar enemigos si no hay cultivo
                    relojRomper.restart();
                }
            }

/// ======================== Primeros drawables =========================///

            window.clear(sf::Color::Black);

            window.setView(Camara);
            window.draw(mapa);
            for (auto& cultivo : _listaCultivos)
            {
                window.draw(*cultivo);
            }
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


/// ========================= General ========================= ///

            mouse.update(window);


/// ======================== Update del Ciclo dia y noche ========================= ///

            _tiempoDiaAcumulado += deltatime / 1000.0f;
            float tiempoActualSegundos = _tiempoDiaAcumulado;
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


            static bool diaReseteado = false;

            if (hora == 6 && !diaReseteado)
            {
                regenerarRecursos(listaEstructuraRandom);
                cout << "¡Un nuevo dia comienza! La isla se ha regenerado." << endl;
                diaReseteado = true; // Marcamos que ya reseteamos hoy
            }

            if (hora == 7)
            {
                diaReseteado = false; // Preparamos el flag para el siguiente dia
            }
            float reduccion = hambrePorSegundo * (deltatime / 1000.0f);
            character.setHambre(character.getHambre() - reduccion);


/// ======================== COMANDOS =========================///

            character.cmd(deltatime);
            sf::Vector2f PosicionJugador = character.getPosition();



            ///Mostramos la vida del jugador

//    cout << character.getVida() << endl;





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
/// ======================== COLISIONES ANIMALES =========================///


sf::FloatRect rectEspada = character.getAreaAtaque();

for (auto it = animales.begin(); it != animales.end();)
{
    // 1. SETUP DEL PUNTERO
    Mob* mobBase = it->get();
    Animal* animal = dynamic_cast<Animal*>(mobBase);

    // 2. UPDATE GENERAL
    mobBase->update(PosicionJugador, deltatime);

    // Colisión con el Mapa
    for (auto& colisionadorMapa : mapa._colisiones) {
        animal->chocar(colisionadorMapa);
    }

    // 3. ORDEÑAR (Click Derecho)
    // Mantenemos esto con Click Derecho para que no ataque sin querer al ordeñar
    if (animal != nullptr && sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        if (animal->getGlobalBounds().contains(posMouseWorld))
        {
            Item* itemEnMano = inv.getItemEnMano();
            // Pasamos inv y fabItems como en tu código original
            if (animal->intentarOrdeniar(character.getPosition(), itemEnMano, fabItems, inv))
            {
                cout << "Ordeñada!!" << endl;
            }
        }
    }

    if (character.getColisionador().detectorDeColision(animal->getColisionador()))
    {
        sf::Vector2f direccionEmpuje = animal->getPosition() - character.getPosition();
        float magnitud = sqrt(direccionEmpuje.x*direccionEmpuje.x + direccionEmpuje.y*direccionEmpuje.y);

        if (magnitud > 0) {
            direccionEmpuje /= magnitud;
            animal->move(direccionEmpuje * 2.f); // Empuje suave físico
        }

    }

    if (golpeHabilitado)
    {
        sf::FloatRect rectAnimal = animal->getColisionador().getColision();

        if (rectEspada.intersects(rectAnimal))
        {
            // --- CÁLCULO DE DAÑO ---
            Item* itemEnMano = inv.getItemEnMano();
            TipoMaterial matAnimal = animal->getMaterial(); // recorda tener esto en Animal/Mob
            float danioFinal = 1.0f;

            if (itemEnMano != nullptr)
            {
                danioFinal = itemEnMano->obtenerFuerza(matAnimal);
                itemEnMano->usar();

                if (itemEnMano->estaRota()) {
                    inv.consumirItemEnSlot(inv.getInventarioResumido()->getSlotSeleccionado(), 1);
                }
            }

            // --- APLICAR DAÑO ---
            animal->bajarVida(danioFinal);
            cout << "¡Hit! Daño: " << danioFinal << endl;

            // --- KNOCKBACK FUERTE POR GOLPE ---
            sf::Vector2f empujeGolpe = animal->getPosition() - character.getPosition();
            float mag = sqrt(empujeGolpe.x*empujeGolpe.x + empujeGolpe.y*empujeGolpe.y);
            if (mag > 0) {
                empujeGolpe /= mag;
                animal->move(empujeGolpe * 20.0f); // Empuje fuerte del golpe
            }
        }
    }

    // 6. VERIFICAR MUERTE
    if (animal->getVida() <= 0)
    {
        animal->soltarLoot(fabItems, listaLoots);
        it = animales.erase(it); // Borramos y actualizamos iterador
    }
    else
    {
        mobBase->move(mobBase->getVelocidad());
        ++it; // Avanzamos iterador
    }
}
/// ======================== COLISION MAPA =========================///

            for (auto& colisionador : mapa._colisiones)
            {
                character.chocar(colisionador);
            }


            float relacion = (float)window.getSize().x/(float)window.getSize().y;

/// ======================== Estructura RANDOM =========================///

for (auto estructura = listaEstructuraRandom.begin(); estructura != listaEstructuraRandom.end(); )
{
    // Verificamos si la estructura sigue viva
    if (!(*estructura)->estaDestruido())
    {
        window.draw(**estructura);
        (*estructura)->getColisionador().draw(window);

        // A. FÍSICA (Chocar para no atravesar) =======================
        // Siempre chequeamos colisión física para el sliding

             character.chocar((*estructura)->getColisionador());


        // B. ATAQUE (Hitbox separada) ================================
        // Solo entramos si atacaste y la estructura se puede romper
        if (golpeHabilitado && (*estructura)->getRompePorColision())
        {
            // Usamos la HITBOX de la espada, no el cuerpo del personaje
            if (rectEspada.intersects((*estructura)->getColisionador().getColision()))
            {
                Item* itemEnMano = inv.getItemEnMano();
                TipoMaterial matEstructura = (*estructura)->getMaterial();
                float danioFinal = 1.0f; // Daño base (puño)

                // Lógica de Herramientas
                if (itemEnMano != nullptr)
                {
                    danioFinal = itemEnMano->obtenerFuerza(matEstructura);

                    // Solo gastamos durabilidad si realmente golpeamos algo rompible
                    itemEnMano->usar();

                    // Si se rompe, lo sacamos del inventario
                    if (itemEnMano->estaRota())
                    {
                        inv.consumirItemEnSlot(inv.getInventarioResumido()->getSlotSeleccionado(), 1);
                        // CUIDADO: itemEnMano ahora es un puntero inválido, no lo uses más abajo.
                        itemEnMano = nullptr;
                    }
                }

                // Debug
                // cout << "Material: " << (int)matEstructura << " | Dmg: " << danioFinal << endl;

                // Aplicar Daño
                (*estructura)->recibirGolpe(danioFinal);

                // Efecto visual opcional: Vibración o color rojo
                // (*estructura)->setColor(sf::Color::Red); (Si tu estructura lo soporta)
            }
        }

        // Update normal de la estructura
        (*estructura)->update( PosicionJugador, posMouseWorld, Camara, relacion, inv, inventarioCofre, deltatime);

        estructura++; // Avanzamos al siguiente
    }
    else
    {
        // Si está destruido, soltamos loot y borramos
        (*estructura)->liberarLoot(fabItems, listaLoots);
        estructura = listaEstructuraRandom.erase(estructura);
    }
}
/// ======================== COLISION ESTRUCTURA =========================///


            bool seAbrioUnCofre = false;

            for (auto estructura = listaEstructuras.begin(); estructura != listaEstructuras.end(); )
            {
                if ((*estructura)->estaDestruido() == false)
                {
                    if(character.getColisionador().detectorDeColision((*estructura)->getColisionador()))   ///EJEMPLO
                    {


                        character.chocar((*estructura)->getColisionador());

                        if ((*estructura)->getRompePorColision())
                        {
                            (*estructura)->recibirGolpe(5);
                        }
                    }
                    window.draw(**estructura);
                    (*estructura)->update( PosicionJugador, posMouseWorld, Camara, relacion, inv, inventarioCofre, deltatime);
                    if ((*estructura) -> getID() == 8){
                        if ((*estructura) -> estaEnUso()){
                            seAbrioUnCofre = true;
                        }
                    }
                    (*estructura)->generarLoot(listaLoots);

                    estructura++;
                }
                else
                {
                    (*estructura)->liberarLoot(fabItems,listaLoots);
                    estructura = listaEstructuras.erase(estructura);
                }
            }

            ///Ocultar interfaz cofre
            if (seAbrioUnCofre){
                inv.setDesvioDelCentroEnY(-16);
                inventarioCofre.setDesvioDelCentroEnY(96);
            }
            else{
                inv.setDesvioDelCentroEnY(50);
                inventarioCofre.setDesvioDelCentroEnY(-1000);
            }

            inventarioCofre.update(mouse.getPosicion(), Camara, relacion, listaLoots);

/// ======================== INICIO LOOT =========================///

            for (auto it = listaLoots.begin(); it != listaLoots.end();)
            {
                it->update(character.getPosition(),inv);
                window.draw(*it);
                if (it->getLooted()) it = listaLoots.erase(it);
                else it++;

            }
/// ======================== INICIO UPDATE =========================///

            for (auto& cultivo : _listaCultivos)
            {
                cultivo->update(deltatime);
            }

/// ======================== TEST HERRAMIENTAS =========================///


            Item* itemVisual = inv.getItemEnMano();

            if (itemVisual != nullptr)
            {
                character.setItemEnMano(itemVisual->getSprite(), itemVisual->getID());
            }
            else
            {

                character.quitarItemEnMano();
            }

            if (Comandos::getInstancia().mouseIzqRecienPresionado)
            {
                character.iniciarAtaque();
            }
/// ======================== INICIO UPDATE =========================///

            character.update(deltatime);

            character.updateEspada(mouse);
            _minimap.update(character.getPosition());

            verificarTeleports(character);
            actualizarFade(character);

            inv.update(mouse.getPosicion(), Camara, relacion, listaLoots); ///FALLAA

            inv.copiarItemsEnVector(vectorCarga);
            invR.setItems(vectorCarga);




/// ======================== INICIO DRAWABLES =========================///
            invR.update(Camara, relacion);

            window.draw(invR);
            window.draw(inventarioCofre);


            window.draw(inv);

            window.setView(window.getDefaultView());

            window.draw(_interfazEstado);


//            window.draw(nightOverlay);

            window.draw(_minimap);

            window.draw(textReloj);

            if (_enTransicion)
            {
                window.draw(_fadeRect);
            }

/// ======================== CAMARA EFECTO Y CENTRADO =========================///


            lerp(camaraPosicion, character.getPosition(), 0.1f);

            sf::Vector2f tamanoActual = Camara.getSize();
            sf::Vector2f tamanoObjetivo = character.getEstaCorriendo() ? sf::Vector2f(350.f, 350.f) : sf::Vector2f(300.f, 300.f);

            lerp(tamanoActual, tamanoObjetivo, 0.05f);
            Camara.setSize(tamanoActual);

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

void Game::regenerarRecursos(std::list<std::unique_ptr<Estructura>>& listaEstructuras)
{

    listaEstructuras.clear();

    cout << "Isla Reset" << endl;


    int ancho = mapa.getMapWidth();
    int alto = mapa.getMapHeight();
    int tileW = mapa.getTileWidth();
    int tileH = mapa.getTileHeight();

    for (int y = 0; y < alto; y++)
    {
        for (int x = 0; x < ancho; x++)
        {

            int idTile = mapa.getTileID(x, y);
            bool esPasto = (idTile == 28 || idTile == 29 || idTile == 36 || idTile == 37);

            bool esArena = (idTile == 35 || idTile == 79);

            bool esCueva = (idTile == 140);


            float posX = x * tileW;
            float posY = y * tileH;
            int probabilidad = rand() % 1000;

            if (esPasto)
            {


                if (idTile == 103)
                {
                    continue;
                }


                // Digamos que hay un 15% de chance de que aparezca un árbol

                if (probabilidad < 50)
                {
                    listaEstructuras.push_back(_FabricaEstructuras.crearEstructura(posX, posY, 0));
                }

                // 5% de chance (más raro que los árboles)
                else if (probabilidad >= 50 && probabilidad <= 100)
                {
                    listaEstructuras.push_back(_FabricaEstructuras.crearEstructura(posX, posY, 1)); ///PIEDRA
                }
                else if (probabilidad >= 150 && probabilidad <= 200)
                {
                    listaEstructuras.push_back(_FabricaEstructuras.crearEstructura(posX, posY, 11));

                }
                else if (probabilidad >= 250 && probabilidad <= 300)
                {
                    listaEstructuras.push_back(_FabricaEstructuras.crearEstructura(posX, posY, 12));

                }
            }


            else if (esArena)
            {
                if (probabilidad < 100)
                {
                    listaEstructuras.push_back(_FabricaEstructuras.crearEstructura(posX, posY, 10));
                }
            }

            else if (esCueva)
            {
                if (probabilidad < 100)
                {
                    listaEstructuras.push_back(_FabricaEstructuras.crearEstructura(posX, posY, 2));
                }

                if (probabilidad >= 150 && probabilidad <= 200)
                {
                    listaEstructuras.push_back(_FabricaEstructuras.crearEstructura(posX, posY, 3));
                }

                if (probabilidad >= 200 && probabilidad <= 230 )
                {
                    listaEstructuras.push_back(_FabricaEstructuras.crearEstructura(posX, posY, 4));
                }

                if (probabilidad >= 230 && probabilidad <= 240)
                {
                    listaEstructuras.push_back(_FabricaEstructuras.crearEstructura(posX, posY, 5));
                }

            }

        }
    }
}

void Game::iniciarTeletransporte(float x, float y)
{
    if (!_enTransicion)
    {
        _destinoTeleport = sf::Vector2f(x, y);
        _enTransicion = true;
        _estadoFade = 1;
    }
}

void Game::actualizarFade(Personaje& character)
{
    if (!_enTransicion) return;

    float velocidadFade = 500.0f * 0.016f; // Ajusta para hacerlo más rapido o lento

    if (_estadoFade == 1)
    {
        _fadeAlpha += velocidadFade;
        if (_fadeAlpha >= 255.0f)
        {
            _fadeAlpha = 255.0f;


            character.setPosicion(_destinoTeleport.x, _destinoTeleport.y);
//            Camara.setCenter(_destinoTeleport.x, _destinoTeleport.y);

            _estadoFade = 2;
        }
    }

    else if (_estadoFade == 2)
    {
        _fadeAlpha -= velocidadFade;
        if (_fadeAlpha <= 0.0f)
        {
            _fadeAlpha = 0.0f;
            _enTransicion = false;
            _estadoFade = 0;
        }
    }

    _fadeRect.setFillColor(sf::Color(0, 0, 0, static_cast<sf::Uint8>(_fadeAlpha)));
}

void Game::verificarTeleports(Personaje& character)
{
    // Si ya estamos viajando, no chequeamos nada para evitar bucles
    if (_enTransicion) return;

    // Calculamos coordenadas de la grilla
    int tileX = static_cast<int>(character.getPosition().x / 32);
    int tileY = static_cast<int>(character.getPosition().y / 32);

    // ================== CUEVA 1 ==================
    if (tileX == 84 && tileY == 91)
    {
        iniciarTeletransporte(166 * 32, 6 * 32);
    }
    else if (tileX == 166 && tileY == 4)
    {
        iniciarTeletransporte(84 * 32, 93 * 32);
    }

    // ================== CUEVA 2 ==================
    else if (tileX == 51 && tileY == 61)
    {
        iniciarTeletransporte(166 * 32, 46 * 32);
    }
    else if (tileX == 166 && tileY == 44)
    {
        iniciarTeletransporte(51 * 32, 63 * 32);
    }
}


bool Game::esSueloCultivable(int tileID) {
    // IDs de la zona de cultivo que me pasaste
    return (tileID == 163 || tileID == 164 || tileID == 165 || tileID == 166 ||
            tileID == 171 || tileID == 172 || tileID == 173 ||
            tileID == 179 || tileID == 180 || tileID == 181);
}

void Game::intentarPlantar(sf::Vector2f posMouseWorld, InventarioInterfaz& inv) {

    //Validar que tengamos algun item en la mano
    Item* item = inv.getItemEnMano();
    if (item == nullptr) return;

    //Obtener coordenadas del Tile donde se hizo clic
    int tileW = mapa.getTileWidth();
    int tileH = mapa.getTileHeight();
    int tileX = static_cast<int>(posMouseWorld.x / tileW);
    int tileY = static_cast<int>(posMouseWorld.y / tileH);

    //Validar Terreno
    int idSuelo = mapa.getTileID(tileX, tileY);
    if (!esSueloCultivable(idSuelo)) return;

    //Calcular posicion
    float posX = tileX * tileW;
    float posY = tileY * tileH;

    //Chequeo de colision: Validar que no haya YA una planta en ese lugar
    sf::FloatRect rectNuevo(posX + 10, posY + 10, 10, 10);

    for (auto& cultivo : _listaCultivos) {
        if (cultivo->getBounds().intersects(rectNuevo)) {
            return; // Ya hay una planta.
        }
    }

    // Si el ID del item es una semilla valida (31, 32, 33...), nos devuelve el objeto.
    // Si es una espada o cualquier otra cosa, nos devuelve nullptr.
    auto nuevoCultivo = _fabricaCultivos.crearDesdeSemilla(item->getID(), posX, posY);

    if (nuevoCultivo != nullptr) {
        //Agregamos el cultivo a la lista del juego
        _listaCultivos.push_back(std::move(nuevoCultivo));

        // Gasta 1 Semilla del inventario
        inv.consumirItemEnSlot(inv.getInventarioResumido()->getSlotSeleccionado(), 1);

        cout << "Planta creada exitosamente en: " << tileX << ", " << tileY << endl;
    }
}

void Game::intentarCosecharClick(sf::Vector2f posMouseWorld, std::list<Loot>& listaLoots, FabricaItems& fabItems) {

    // 1. Creamos un "apuntador" al principio de la lista
    auto it = _listaCultivos.begin();

    // 2. Recorremos mientras no lleguemos al final
    while (it != _listaCultivos.end()) {

        // Verificamos si el mouse toca este cultivo
        // (*it) nos da el puntero al cultivo actual
        if ((*it)->getBounds().contains(posMouseWorld)) {

            // Intentamos cosechar
            if ((*it)->intentarCosechar(listaLoots, fabItems)) {

                // Si devolvio true (se rompio/cosecho), lo borramos de la lista
                // erase devuelve el puntero al siguiente elemento, pero como hacemos return, no importa tanto
                it = _listaCultivos.erase(it);

                return; // Salimos de la funcion para no romper mas de uno a la vez
            }
        }

        // Si no paso nada, avanzamos al siguiente cultivo
        it++;
    }
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
