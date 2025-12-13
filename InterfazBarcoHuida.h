#pragma once
#include <SFML/Graphics.hpp>
#include "SeleccionRectangulo.h"
#include "InventarioIntefaz.h"
#include <string>

class InterfazBarcoHuida : public sf::Transformable, public sf::Drawable
{
private:
    int _pagina = 0;
    std::string _titulos[4];
    SeleccionRectangulo _botonIzqControlPagina;
    SeleccionRectangulo _botonDerControlPagina;
    bool _completado = false;
    sf::Sprite _sprfondoInterfaz;
    const sf::Texture* _texturaFondoInterfaz;
    SeleccionRectangulo _selectoresAgregarItems[8];
    sf::Font _fuenteTexto;
    sf::Text _textoTitulo;
public:
    InterfazBarcoHuida(const sf::Texture& texturaFondoInterfaz);
    void update(const sf::Vector2f& posGlobalDelMouse, InventarioInterfaz& inventarioJugador);
    void ajustarEscalaAutomaticamente(const sf::View& vista, const float& relacionAspecto);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

