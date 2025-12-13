#pragma once
#include <SFML/Graphics.hpp>
#include "SeleccionRectangulo.h"
#include "InventarioIntefaz.h"
#include "Item.h"
#include <string>
#include <list>
#include <vector>
#include <memory>


class InterfazBarcoHuida : public sf::Transformable, public sf::Drawable
{
private:
    int _pagina = 0;
    std::string _titulos[4];
    std::list<std::unique_ptr<Item>> _ItemsRequeridos[4];
    std::list<sf::Text> _textoExigencia[4];
    std::vector<int> _cantidadNecesaria[4];
    std::vector<SeleccionRectangulo> _selectoresItems[4];
    SeleccionRectangulo _botonIzqControlPagina;
    SeleccionRectangulo _botonDerControlPagina;
    bool _completado = false;
    sf::Sprite _sprfondoInterfaz;
    const sf::Texture* _texturaFondoInterfaz;
    sf::Font _fuenteTexto;
    sf::Text _textoTitulo;
public:
    InterfazBarcoHuida(const sf::Texture& texturaFondoInterfaz, FabricaItems& fabItems);
    void update(const sf::Vector2f& posGlobalDelMouse, InventarioInterfaz& inventarioJugador);
    void ajustarEscalaAutomaticamente(const sf::View& vista, const float& relacionAspecto);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

