#ifndef BARRADEVIDA_H_INCLUDED
#define BARRADEVIDA_H_INCLUDED

#include <SFML/Graphics.hpp>

class BarraDeVida: public sf::Drawable{
private:
    sf::RectangleShape fondo;
    sf::RectangleShape barra;
    float* vidaPtr;              // CAMBIAR: puntero en lugar de referencia
    float* vidaMaxima;

public:
    // Constructor por defecto
    BarraDeVida();

    // Constructor con parámetros
    BarraDeVida(float& vida, float& maxVida);

    void actualizar();
    void setPosition(float x, float y);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    void actualizarColor();
};
#endif // BARRADEVIDA_H_INCLUDED
