#pragma once
#include <SFML/Graphics.hpp>

class CinematicaInicial : public sf::Transformable, public sf::Drawable
{
private:
    bool _completado = false;
    bool _reproducir = false;
    sf::RectangleShape _rectanguloCielo;
    sf::Sprite _sprAvion;
    sf::Sprite _sprAvionFondo;
    sf::Sprite _sprPersonaje;
    sf::Sprite _sprNubes;
    sf::Sprite _sprTurbina;
    float _incSeno = 0;
    float _incSeno2 = 0;
    int _etapaAnimacion = 0;
    float _movimientoAvion = 1;
    sf::Clock _tiempoEnEtapa;
public:
    CinematicaInicial(const sf::Texture& texturaPersonaje, const sf::Texture& texturaAvion, const sf::Texture& texturaTurbina, const sf::Texture& texturaNubes);
    void update();
    void ajustarEscalaAutomaticamente(const sf::View& vista, const float& relacionAspecto);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    bool getCompletado();
    bool estaReproduciendo();
    void reproducir();
};
