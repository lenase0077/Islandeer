#pragma once
#include <SFML/Graphics.hpp>
#include "SeleccionRectangulo.h"
#include "InventarioIntefaz.h"
#include <vector>
#include <list>

class SelectorDeOpciones : public sf::Transformable, public sf::Drawable
{
private:
    int _opcionSeleccionada = -1;
    bool _abierto = false;
    std::vector<SeleccionRectangulo> _selectoresOpciones;
    std::list<sf::Text> _textoOpciones;
    sf::Text _titulo;
    const sf::Font* _fuenteOpciones;
    sf::RectangleShape _resaltadoSeleccion;
    sf::RectangleShape _fondo;
public:
    SelectorDeOpciones(const std::string& tituloOpcion,const sf::Font& fuenteTexto);

    void setAbierto(bool nuevoEstado);
    bool getAbierto();
    int getOpcionSeleccionada();
    void resetOpcionSeleccionada();

    void agregarOpcion(std::string tituloOpcion = "TITULO OPCION");

    void update(const sf::Vector2f& posGlobalDelMouse, InventarioInterfaz& inventarioJugador);

    void ajustarEscalaAutomaticamente(const sf::View& vista, const float& relacionAspecto);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

