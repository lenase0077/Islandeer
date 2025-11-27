#include "Comando.h"

void Comandos::actualizar()
    {
        // --- 1. Lógica del Teclado ---

        teclaArriba    = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
        teclaAbajo     = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
        teclaIzquierda = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
        teclaDerecha   = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
        teclaCorrer    = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);
        teclaTomarTodo    = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);

        // --- 2. Lógica del Mouse ---

        bool estadoActualMouseIzq = sf::Mouse::isButtonPressed(sf::Mouse::Left);

        mouseIzqRecienPresionado = (estadoActualMouseIzq) && (!_mouseIzqAnterior);
        mouseIzqRecienSoltado = (!estadoActualMouseIzq) && (_mouseIzqAnterior);
        mouseIzqPresionado = estadoActualMouseIzq;
        _mouseIzqAnterior = estadoActualMouseIzq;

        // --- 3. Lógica de Doble Click ---

        mouseIzqDobleClick = false;

        if (mouseIzqRecienPresionado)
        {
            if (_relojDobleClick.getElapsedTime().asMilliseconds() < 250) {
                mouseIzqDobleClick = true;
            }

            _relojDobleClick.restart();
        }
    }
