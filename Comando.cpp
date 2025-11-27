#include "Comando.h"

void Comandos::actualizar()
    {


        sentidoScroll = 0;

        // --- 1. Logica del Teclado ---

        teclaArriba    = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
        teclaAbajo     = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
        teclaIzquierda = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
        teclaDerecha   = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
        teclaCorrer    = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);
        teclaTomarTodo    = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);


        bool estadoQ = sf::Keyboard::isKeyPressed(sf::Keyboard::Q);

        teclaTirarRecienPresionada = estadoQ && !_teclaTirarAnterior;
        teclaTirar = estadoQ;
        _teclaTirarAnterior = estadoQ;




        // --- 2. Logica del Mouse ---

        bool estadoActualMouseIzq = sf::Mouse::isButtonPressed(sf::Mouse::Left);

        mouseIzqRecienPresionado = (estadoActualMouseIzq) && (!_mouseIzqAnterior);
        mouseIzqRecienSoltado = (!estadoActualMouseIzq) && (_mouseIzqAnterior);
        mouseIzqPresionado = estadoActualMouseIzq;
        _mouseIzqAnterior = estadoActualMouseIzq;



        // --- 2.1 Logica del Mouse DERECHO  ---
        bool estadoActualMouseDer = sf::Mouse::isButtonPressed(sf::Mouse::Right);

        mouseDerRecienPresionado = (estadoActualMouseDer) && (!_mouseDerAnterior);
        mouseDerRecienSoltado    = (!estadoActualMouseDer) && (_mouseDerAnterior);
        mouseDerPresionado       = estadoActualMouseDer;
        _mouseDerAnterior        = estadoActualMouseDer;

        // --- 3. Logica de Doble Click ---

        mouseIzqDobleClick = false;

        if (mouseIzqRecienPresionado)
        {
            if (_relojDobleClick.getElapsedTime().asMilliseconds() < 250) {
                mouseIzqDobleClick = true;
            }

            _relojDobleClick.restart();
        }

        // --- 4 Logica de tecla E (inv) ---

        bool estadoE = sf::Keyboard::isKeyPressed(sf::Keyboard::E);

        teclaInventarioRecienPresionada = estadoE && !_teclaInventarioAnterior;
        _teclaInventarioAnterior = estadoE;

        // --- 4 Logica de tecla E (inv) ---


        slotSeleccionadoTeclado = -1;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) slotSeleccionadoTeclado = 0;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) slotSeleccionadoTeclado = 1;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) slotSeleccionadoTeclado = 2;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) slotSeleccionadoTeclado = 3;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) slotSeleccionadoTeclado = 4;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)) slotSeleccionadoTeclado = 5;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7)) slotSeleccionadoTeclado = 6;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8)) slotSeleccionadoTeclado = 7;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9)) slotSeleccionadoTeclado = 8;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)) slotSeleccionadoTeclado = 9;
}

void Comandos::registrarScroll(float delta)
{
    if (delta > 0) sentidoScroll = -1;
    else if (delta < 0) sentidoScroll = 1;
}
