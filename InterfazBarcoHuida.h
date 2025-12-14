#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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
    bool _oculto = true;
    int _pagina = 0;
    std::string _titulos[4];
    std::list<std::unique_ptr<Item>> _ItemsRequeridos[4];
    std::list<sf::Text> _textoExigencia[4];
    std::vector<int> _cantidadNecesaria[4];
    std::vector<SeleccionRectangulo> _selectoresItems[4];
    bool _paginaCompletada[4];
    sf::RectangleShape _bordeSeleccion;
    SeleccionRectangulo _botonIzqControlPagina;
    SeleccionRectangulo _botonDerControlPagina;
    bool _completado = false;
    sf::Sprite _sprfondoInterfaz;

    const sf::Texture* _texturaFondoInterfaz;
    sf::Font _fuenteTexto;
    sf::Text _textoTitulo;

    const sf::Texture* _texturaBotonesDePagina;
    sf::Sprite _sprBotonPagSiguiente;
    sf::Sprite _sprBotonPagAnterior;

    std::vector<sf::RectangleShape> _lineaSubRayado[4];

    //variables de sonido
    sf::Sound _sonidoLapiz;
    sf::SoundBuffer _bufferSonidoLapiz;
public:
    InterfazBarcoHuida(const sf::Texture& texturaFondoInterfaz, const sf::Texture& texturaBotonesDePagina, FabricaItems& fabItems);
    void update(const sf::Vector2f& posGlobalDelMouse, InventarioInterfaz& inventarioJugador);
    void ajustarEscalaAutomaticamente(const sf::View& vista, const float& relacionAspecto);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    bool getCompletado();
    bool getOculto();
    void setOculto(bool nuevoEstado);
    void setVolumen (float Volumen);
};

