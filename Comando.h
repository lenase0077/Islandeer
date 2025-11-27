#pragma once
#include <SFML/Graphics.hpp>

class Comandos
{
private:
    Comandos() {};

    sf::Clock _relojDobleClick;
    bool _mouseIzqAnterior = false;
    bool _mouseDerAnterior = false;
    bool _teclaTirarAnterior = false;

    Comandos(const Comandos&) = delete;
    void operator=(const Comandos&) = delete;


public:

    static Comandos& getInstancia()
    {
        static Comandos instancia; // Se crea solo una vez
        return instancia;
    }


    void actualizar();

    bool teclaArriba    = false;
    bool teclaAbajo     = false;
    bool teclaIzquierda = false;
    bool teclaDerecha   = false;
    bool teclaCorrer    = false;
    bool teclaTomarTodo = false;


    bool mouseIzqPresionado = false;
    bool mouseIzqRecienPresionado = false;
    bool mouseIzqRecienSoltado = false;
    bool mouseIzqDobleClick = false;

    bool mouseDerPresionado = false;
    bool mouseDerRecienPresionado = false;
    bool mouseDerRecienSoltado = false;

    bool teclaTirar = false;
    bool teclaTirarRecienPresionada = false;

    bool _teclaInventarioAnterior = false;
    bool teclaInventarioRecienPresionada = false;





};
