#include "InterfazEstado.h"
#include <iostream>

InterfazEstado::InterfazEstado()
{
    // Posici¢n base
    float posX = 980.f;
    float posY_Vida = 705.f;

    configurarBarra(_barraVida, sf::Color(220, 20, 60), {posX, posY_Vida}, "Corazon.png");
    configurarBarra(_barraEnergia, sf::Color(255, 215, 0), {posX - 40, posY_Vida}, "Rayo.png");
    configurarBarra(_barraHambre, sf::Color(205, 133, 63), {posX - 80, posY_Vida}, "Papa.png");
}

void InterfazEstado::configurarBarra(Barra& barra, sf::Color colorRelleno, sf::Vector2f posicion, std::string archivoIcono)
{
    sf::Vector2f tamanoBarra(20.f, 100.f);

    //FONDO
    barra.fondo.setSize(tamanoBarra);
    barra.fondo.setFillColor(sf::Color(20, 20, 20, 200)); // Gris muy oscuro
    barra.fondo.setPosition(posicion.x, posicion.y - tamanoBarra.y); // Crece hacia arriba

    //BORDE (Pixel)
    barra.borde.setSize({tamanoBarra.x + 4, tamanoBarra.y + 4});
    barra.borde.setFillColor(sf::Color::Transparent);
    barra.borde.setOutlineThickness(2);
    barra.borde.setOutlineColor(sf::Color(220, 220, 220)); // Blanco/Gris claro
    barra.borde.setPosition(posicion.x - 2, posicion.y - tamanoBarra.y - 2);

    //RELLENO
    barra.relleno.setSize(tamanoBarra);
    barra.relleno.setFillColor(colorRelleno);
    barra.relleno.setOrigin(0, tamanoBarra.y);
    barra.relleno.setPosition(posicion.x, posicion.y); // Base de la barra

    //ICONOS
    if (barra.texturaIcono.loadFromFile(archivoIcono))
    {
        barra.texturaIcono.setSmooth(false);

        barra.spriteIcono.setTexture(barra.texturaIcono);

        // CENTRAMOS EL ICONO
        barra.spriteIcono.setOrigin(8, 8);

        barra.spriteIcono.setPosition(posicion.x + 10, posicion.y - tamanoBarra.y - 25);

        barra.spriteIcono.setScale(2.0f, 2.0f);
    }
    else
    {
        std::cout << "No se pudo cargar icono: " << archivoIcono << std::endl;
    }
}

void InterfazEstado::update(float vida, float maxVida, float energia, float maxEnergia, float hambre, float maxHambre)
{
    // Calculamos porcentajes (0.0 a 1.0)
    float ratioVida = vida / maxVida;
    float ratioEnergia = energia / maxEnergia;
    float ratioHambre = hambre / maxHambre;

    // Evitamos negativos
    if (ratioVida < 0) ratioVida = 0;
    if (ratioEnergia < 0) ratioEnergia = 0;
    if (ratioHambre < 0) ratioHambre = 0;

    float altoVida = 100.f * ratioVida;
    float altoEnergia = 100.f * ratioEnergia;
    float altoHambre = 100.f * ratioHambre;

    // Actualizamos la altura
    _barraVida.relleno.setSize({20.f, altoVida});
    _barraVida.relleno.setOrigin(0, altoVida);

    _barraEnergia.relleno.setSize({20.f, altoEnergia});
    _barraEnergia.relleno.setOrigin(0, altoEnergia);

    _barraHambre.relleno.setSize({20.f, altoHambre});
    _barraHambre.relleno.setOrigin(0, altoHambre);

}

void InterfazEstado::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // Dibujamos Hambre
    target.draw(_barraHambre.fondo);
    target.draw(_barraHambre.relleno);
    target.draw(_barraHambre.borde);
    target.draw(_barraHambre.spriteIcono);

    // Dibujamos Energia
    target.draw(_barraEnergia.fondo);
    target.draw(_barraEnergia.relleno);
    target.draw(_barraEnergia.borde);
    target.draw(_barraEnergia.spriteIcono);

    // Dibujamos Vida
    target.draw(_barraVida.fondo);
    target.draw(_barraVida.relleno);
    target.draw(_barraVida.borde);
    target.draw(_barraVida.spriteIcono);
}
