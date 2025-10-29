#include <SFML/Graphics.hpp>
#include "InventarioIntefaz.h"
#include "InventarioResumidoInterfaz.h"
#include <iostream>
#include <ctime>
#include "Loot.h"

using namespace std;

int main() {
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(1024, 1024), "SFML works!");

    sf::View camara;
    camara.setSize(900,900);
    camara.setCenter(800,500);

    sf::Clock clock;

    Loot l1(sf::Vector2f(500,500), 26, 10);

    InventarioInterfaz inventario;
    InventarioResumido invBarra;

    inventario.agregarItem(44,30);
    inventario.agregarItem(26,30);

    window.setFramerateLimit(75);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            invBarra.cambiarSlotsConEventos(event);
            inventario.controlAbrirCerrarInventario(event);

        }

        window.clear();

        int ValorAleatorio = rand() % 54;

        inventario.agregarItem(ValorAleatorio);



        // Calcula los FPS
        float dt = clock.restart().asSeconds();
        float fps = 1.f / dt;

        cout << "FPS: " << std::to_string(static_cast<int>(fps)) << endl;
        //cout << inventario.agregarItem(15) << endl;

        window.setView(camara);

        //camara.setSize(sf::Vector2f(camara.getSize().x + 0.8, camara.getSize().y + 0.8));

        sf::Mouse mouse;

        sf::Vector2f posGlobalDelMouse = window.mapPixelToCoords(mouse.getPosition(window));

        float relacion = (float)window.getSize().x/(float)window.getSize().y;

        inventario.update(posGlobalDelMouse, mouse, camara, relacion);
        window.draw(inventario);

        invBarra.setItems(inventario.obtenerPunteroInventario());
        invBarra.update(camara, relacion);

        window.draw(invBarra);

        l1.update();
        window.draw(l1);


        window.display();

        /// LA SEMANA QUE VIENE
        /// TENERLO TODO EN GITHUB CON COMMIT Y RAMAS
        /// TENER EL OBJETO LOOT

    }

    return 0;
}











