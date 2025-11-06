#pragma once
#include <SFML/Graphics.hpp>

class Comandos
{
private:
    Comandos() {};

    sf::Clock _relojDobleClick;
    bool _mouseIzqAnterior = false;

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

    bool mouseIzqPresionado = false;
    bool mouseIzqRecienPresionado = false;
    bool mouseIzqRecienSoltado = false;
    bool mouseIzqDobleClick = false;




};
