#include <iostream>
#include "Horno.h"
#include <cmath>
using namespace std;

Horno::Horno(sf::Texture& texturaBloques, float posX, float posY, int id)
: Estructura (texturaBloques,posX,posY,id)
{
    _estaCocinando = false;
    _tiempoCoccionActual = 0;
    _tiempoParaCocinar = 5000;
    _seRompePorColision = false;
    _idProductoCocinandose = -1;
    _sprite.setColor(sf::Color::White);
}

int Horno::IDProductoCocinable(int IDItem)
{
    switch(IDItem)
    {
        case 11: return 20;
        case 12: return 21;
        case 40: return 41;
        case 45: return 46;
        case 47: return 48;
        default: return -1;
    }
}

void Horno::update(const sf::Vector2f& posicionJugador, const sf::Vector2f& posGlobalDelMouse, const sf::Mouse& mouse, const sf::View& vista, const float& relacionAspecto, InventarioInterfaz& inventario, float deltatime)
{
    float distanciaJugador = sqrt(pow(posicionJugador.x - getPosition().x,2) + pow(posicionJugador.y - getPosition().y,2));
    bool estaCerca = (distanciaJugador < 100);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        cout << "Click detectado en: " << posGlobalDelMouse.x << ", " << posGlobalDelMouse.y << endl;
        cout << "Posicion Horno: " << getPosition().x << ", " << getPosition().y << endl;
        cout << "Distancia Jugador: " << distanciaJugador << endl;
    }

    ///Efectos Visuales
    if (estaCerca && !_estaCocinando)
    {
        _sprite.setColor(sf::Color(200,200,255));
    }
    else if (!_estaCocinando)
    {
        _sprite.setColor(sf::Color::White);
    }
    else if (_estaCocinando)
    {
        int tiempo = (int)(_tiempoCoccionActual / 200);
        if (tiempo % 2 == 0)
        {
            _sprite.setColor(sf::Color(255,150,150));
        }
        else
        {
            _sprite.setColor(sf::Color(255,200,200));
        }
    }

    ///Click
    if (estaCerca && sf::Mouse::isButtonPressed(sf::Mouse::Right) && !_estaCocinando)
    {
        if (fueClickeado(posGlobalDelMouse))
        {
            cout << "1. Click valido sobre el horno." << endl;
            InventarioResumido* InvResum = inventario.getInventarioResumido();

            if (InvResum != nullptr)
            {
                cout << "2. Inventario Resumido ENCONTRADO." << endl;
                Item* itemEnMano = InvResum->getItem(InvResum->getSlotSeleccionado());

                if (itemEnMano!=nullptr)
                {
                    cout << "3. Item en mano detectado ID: " << itemEnMano->getID() << endl;
                    ///Verificamos que sea un item cocinable
                    int IDResulutado = IDProductoCocinable(itemEnMano->getID());

                    if (IDResulutado != -1)
                    {
                        cout << "4. El item ES cocinable." << endl;
                        if (inventario.buscarItems(19,5) != -1)
                        {
                            cout << "5. Carbon suficiente. COCINANDO..." << endl;

                            inventario.quitarItem(19,5);

                            inventario.consumirItemEnSlot(InvResum->getSlotSeleccionado(),1);

                            _estaCocinando = true;
                            _idProductoCocinandose = IDResulutado;
                            _tiempoCoccionActual = 0;
                        }

                        else { cout << "ERROR: Falta Carbon (ID 19)." << endl; }
                    }
                    else { cout << "ERROR: El item ID " << itemEnMano->getID() << " no se puede cocinar." << endl; }
                }
                else { cout << "ERROR: No tenes ningun item en la mano (Slot vacio)." << endl; }
            }
            else { cout << "ERROR CRITICO: El inventario resumido es NULL. Falta el setInventarioResumido en Game.cpp" << endl; }
        }
    }

    if (_estaCocinando)
    {
        _tiempoCoccionActual += deltatime;

        if (_tiempoCoccionActual >= _tiempoParaCocinar)
        {
            _sprite.setColor(sf::Color::Green);
        }
    }
}

bool Horno::fueClickeado(const sf::Vector2f& posMouse)
{
    // Obtenemos la posicion del horno
    float x = getPosition().x;
    float y = getPosition().y;

    float ancho = 32.0f;
    float alto = 32.0f;

    // Verificamos si el mouse esta adentro del cuadrado
    bool enX = (posMouse.x >= x && posMouse.x <= (x + ancho));
    bool enY = (posMouse.y >= y && posMouse.y <= (y + alto));

    return (enX && enY);
}

bool Horno::terminarDeCocinar()
{
    return(_estaCocinando && _tiempoCoccionActual >= _tiempoParaCocinar);
}

void Horno::generarLoot (std::list<Loot>& listaLoot)
{
    if (terminarDeCocinar())
    {
        sf::Vector2f posLootProduct = getPosition();
        posLootProduct.x += 16;
        posLootProduct.y += 32;

        listaLoot.emplace_back(_fabItems, posLootProduct, _idProductoCocinandose);

        _estaCocinando = false;
        _tiempoCoccionActual = 0;
        _idProductoCocinandose = -1;
        _sprite.setColor(sf::Color::White);
    }

}

