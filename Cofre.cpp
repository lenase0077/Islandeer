#include <iostream>
#include "Cofre.h"
using namespace std;

Cofre::Cofre(sf::Texture& texturaBloques, float posX, float posY, int id)
    : Estructura (texturaBloques,posX,posY,id)
{
    setVida(100);
    _seRompePorColision = false;
}

void Cofre::update(const sf::Vector2f& posicionJugador, const sf::Vector2f& posGlobalDelMouse, const sf::View& vista, const float& relacionAspecto, InventarioInterfaz& inventario, InventarioInterfaz& inventarioCofre, float deltatime)
{
    // 1. Detectar si el jugador interact£a para abrir el cofre
    // (Tu l¢gica de abrir/cerrar aqu¡...)

    float distanciaJugador = sqrt(pow((posicionJugador.x + 8) - (getPosition().x + 16),2) + pow((posicionJugador.y + 8) - (getPosition().y + 16),2));

    if (distanciaJugador < 25)
    {

        _sprite.setColor(sf::Color::Red);

        if (inventarioCofre.getAbierto())
        {
            if (!_enUso)
            {
                _enUso = true;
                // 2. ENLACE MAGICO:
                // Le pasamos al cofre el puntero del item en mano del JUGADOR
                inventarioCofre.enlazarItemEnMano(inventario.obtenerPunteroItemEnMano());

                cargarContenido( inventarioCofre);
                //Siguientes pasos
                /*
                - Al cerrar o alejarse se debe guardar en una matriz la cantidad y el id de los items que existen en inventario cofre,
                - al abrir llamamos una sola vez a la funcion para cargar los items del inventario, internamente ya deberia funcionar con la fabrica
                */
            }

        }
        else
        {
            /*// Si se cierra, desenlazamos por seguridad (opcional)
            inventarioCofre.enlazarItemEnMano(nullptr);*/
            if (_enUso)
            {
                // 1. Guardamos lo que haya en la interfaz dentro de los arrays de ESTE cofre
                guardarContenido(inventarioCofre);

                // 3. Desenlazamos por seguridad
                inventarioCofre.enlazarItemEnMano(nullptr);

                _enUso = false;
            }
        }
    }
    else
    {
        _sprite.setColor(sf::Color::White);

        if (_enUso)
        {
            // 1. Guardamos lo que haya en la interfaz dentro de los arrays de ESTE cofre
            guardarContenido(inventarioCofre);

            // 3. Desenlazamos por seguridad
            inventarioCofre.enlazarItemEnMano(nullptr);

            _enUso = false;
        }
    }
}

void Cofre::cargarContenido(InventarioInterfaz& inventarioCofre)
{
    // El cofre le "pasa" sus items a la interfaz visual
    inventarioCofre.recibirItemsDe(_itemsGuardados);

    // NOTA: Ahora _itemsGuardados del cofre est  lleno de nullptr,
    // porque los items viven temporalmente en la interfaz.
    cout << "Cofre abierto: Items movidos a la interfaz." << endl;
}

void Cofre::guardarContenido(InventarioInterfaz& inventarioCofre)
{
    // La interfaz le devuelve los items al cofre
    inventarioCofre.transferirItemsHacia(_itemsGuardados);

    cout << "Cofre cerrado: Items regresaron al cofre." << endl;
}

