#pragma once
#include "SeleccionRectangulo.h"
#include "SFML/Graphics.hpp"
#include <string>

class MisionGUI : public sf::Transformable, public sf::Drawable
{
private:
    bool _oculto = false;
    bool _completado = false;
    SeleccionRectangulo _botonReclamar;
    sf::Text _textoTitulo; // Max 18 caracteres.
    sf::Text _textoExplicacion; // Breve descripcion de la mision.
    int _recompensa;
    sf::Text _textoMonedas;
    sf::Sprite _sprFondo;
    sf::Sprite _sprBotonReclamar;
    const sf::Font* _fuentesTextos;
public:
    MisionGUI(const sf::Font& fuenteTextos,
              const sf::Texture& texturaMision,
              const std::string& titulo = "TITULO MISION",
              const std::string& explicacion = "Aqui va la explicacion de la mision a realizar",
              const int& recompensa = 1);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void setOculto(bool nuevoEstado);
    bool getOculto();
    bool getCompletado();
    void ajustarEscalaAutomaticamente(const sf::View& vista, const float& relacionAspecto);
    void update(const sf::Vector2f& posGlobalDelMouse);
};

