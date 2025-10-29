#include <iostream>
#include "BarraDeVida.h"
#include <SFML/Graphics.hpp>

using namespace std;

// Constructor por defecto
BarraDeVida::BarraDeVida()
    : vidaPtr(nullptr), vidaMaxima(nullptr) {

    // Configuración básica - TAMAÑOS NUEVOS
    fondo.setSize(sf::Vector2f(18.f, 6.f));      // 18x6 (fondo un poco más grande)
    fondo.setFillColor(sf::Color(50, 50, 50));   // Color gris oscuro
    fondo.setOutlineThickness(1.f);              // Borde más delgado
    fondo.setOutlineColor(sf::Color::White);     // Borde blanco

    barra.setSize(sf::Vector2f(16.f, 4.f));      // 16x4 (tamaño interior)
    barra.setFillColor(sf::Color::Green);        // Color inicial
}

// Constructor con parámetros
BarraDeVida::BarraDeVida(float& vida, float& vidaMaxima)
    : vidaPtr(&vida), vidaMaxima(&vidaMaxima) {

    // Configuración básica - TAMAÑOS NUEVOS
    fondo.setSize(sf::Vector2f(18.f, 6.f));      // 18x6 (fondo un poco más grande)
    fondo.setFillColor(sf::Color(50, 50, 50));   // Color gris oscuro
    fondo.setOutlineThickness(1.f);              // Borde más delgado
    fondo.setOutlineColor(sf::Color::White);     // Borde blanco

    barra.setSize(sf::Vector2f(16.f, 4.f));      // 16x4 (tamaño interior)
    actualizarColor();
}

void BarraDeVida::actualizar() {
    // Verificar que el puntero no sea nulo
    if (vidaPtr == nullptr) return;

    // Calcular ancho basado en porcentaje de vida - USAR 16.f AHORA
    float healthWidth = (*vidaPtr / *vidaMaxima) * 16.f;  // Ancho máximo 16
    barra.setSize(sf::Vector2f(healthWidth, 4.f));       // Mantener alto en 4

    actualizarColor();
}

void BarraDeVida::setPosition(float x, float y) {
    fondo.setPosition(x, y);
    // Centrar la barra interior en el fondo (18-16=2, 6-4=2 → 1px de margen cada lado)
    barra.setPosition(x + 1.f, y + 1.f);
}

void BarraDeVida::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(fondo);
    target.draw(barra);
}

void BarraDeVida::actualizarColor() {
    // Verificar que el puntero no sea nulo
    if (vidaPtr == nullptr) return;

    float porcentaje = *vidaPtr / *vidaMaxima;

    if (porcentaje > 0.6f) {
        barra.setFillColor(sf::Color::Green);
    } else if (porcentaje > 0.3f) {
        barra.setFillColor(sf::Color::Yellow);
    } else {
        barra.setFillColor(sf::Color::Red);
    }
}
