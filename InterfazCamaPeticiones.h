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


class InterfazCamaPeticiones : public sf::Transformable, public sf::Drawable
{
private:
    bool _oculto = true;
    std::string _titulos;
    std::list<std::unique_ptr<Item>> _ItemsRequeridos;
    std::list<sf::Text> _textoExigencia;
    std::vector<int> _cantidadNecesaria;
    std::vector<SeleccionRectangulo> _selectoresItems;
    sf::RectangleShape _bordeSeleccion;
    bool _completado = false;
    sf::Sprite _sprfondoInterfaz;

    const sf::Texture* _texturaFondoInterfaz;
    sf::Text _textoTitulo;

    std::vector<sf::RectangleShape> _lineaSubRayado;

    //variables de sonido
    sf::Sound _sonidoLapiz;
    sf::SoundBuffer _bufferSonidoLapiz;
public:
    InterfazCamaPeticiones(const sf::Texture& texturaFondoInterfaz, const sf::Font& fuente, FabricaItems& fabItems);
    void update(const sf::Vector2f& posGlobalDelMouse, InventarioInterfaz& inventarioJugador);
    void ajustarEscalaAutomaticamente(const sf::View& vista, const float& relacionAspecto);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    bool getCompletado();
    bool getOculto();
    void setOculto(bool nuevoEstado);
    void setVolumen (float Volumen);

    void setCantidadesPagina(int pagina, const std::vector<int>& datosCargados);
    void recalcularEstadoCompletado();

};

