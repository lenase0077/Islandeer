#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class InterfazEstado : public sf::Drawable
{
public:
    InterfazEstado();
    void update(float vida, float maxVida, float energia, float maxEnergia, float hambre, float maxHambre);

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    struct Barra {
        sf::RectangleShape fondo;
        sf::RectangleShape relleno;
        sf::RectangleShape borde;
        sf::Texture texturaIcono;
        sf::Sprite spriteIcono;
    };

    Barra _barraVida;
    Barra _barraEnergia;
    Barra _barraHambre;

    void configurarBarra(Barra& barra, sf::Color colorRelleno, sf::Vector2f posicion, std::string archivoIcono);
};
