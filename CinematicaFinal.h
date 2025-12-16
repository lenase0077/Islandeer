#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class CinematicaFinal : public sf::Transformable, public sf::Drawable
{
private:
    sf::Text _textoCreditos;
    bool _completado = false;
    bool _reproducir = false;
    float _limiteTexto;
    sf::RectangleShape _rectanguloAgua;
    sf::Sprite _barco;
    sf::Sprite _personaje;
    float _incSeno = 0;
public:
    CinematicaFinal(const sf::Texture& texturaPersonaje,const sf::Texture& texturaBarco, const sf::Texture& texturaAgua, const sf::Font& fuenteTexto, const std::string textoCreditos = "TEXTO DEFAULT");
    void update();
    void ajustarEscalaAutomaticamente(const sf::View& vista, const float& relacionAspecto);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    bool getCompletado();
    bool estaReproduciendo();
    void reproducir();
};
