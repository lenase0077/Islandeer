#pragma once
#include "SeleccionRectangulo.h"
#include "Item.h"
#include "ItemDescripcion.h"
#include <SFML/Graphics.hpp>
#include <string>

/***
NOTAS PARA EL CORRECTO MANEJO DEL OBJETO:
Este objeto controla y dibuja el inventario organizando sus items y cuadrillas.
Importante:
- Para la deteccion del mouse dentro de las celdas se usa un vector de
ObjetoSeleccion;
- Para la representacion de los items se utiliza un vector de Item.
- Los ESPACIOS VACIOS DEL INVENTARIO, a nivel codigo, son objetos de tipo
Item con una ID == -1;
*/

class InventarioInterfaz : public sf::Drawable, sf::Transformable
{
private:
    bool _primerVuelta = false;
    bool _abierto = false;
    bool _clickIzquierdoDisponible;
    bool _clickDerechoDisponible;
    bool _botonAbrirInventarioDisponible = true;
    bool _hayItemEnMano;
    bool _izquierdoPresionadoAnterior = false;
    int _indiceUltimoItemAnalizado;
    sf::Clock _timerDobleClick2;
    int _contadorClicksIzquierdo = 0;
    float _posX, _posY;
    sf::Vector2f _posicionEscondite;
    sf::Vector2f _posicionAbierto;
    ItemDescripcion _descripcion;
    Item _inventarioItems[30];
    Item _itemEnMano;
    SeleccionRectangulo _areasSeleccion[30];
    std::string _nombreDireccionTextura;
    sf::Texture _texturaFondo;
    sf::Sprite _sprFondoInventario;
    sf::Vector2f _escala;

    ///Metodos privados
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    bool sumarItems(Item& ItemIncrementador, Item& ItemIncrementado);
    void ajustarEscalaAutomaticamente(const sf::View& vista, const float& relacionAspecto);

public:
    /// Constructores
    InventarioInterfaz(sf::Texture& texturaItems,std::string nombreDireccionTextura = "Inventario.png");

    /// Getters
    float getPosX();
    float getPosY();
    bool getAbierto();
    std::string getNombreDireccionTextura();
    sf::Vector2f getPosicionEscondite();
    sf::Vector2f getPosicionAbierto();


    /// Setters
    void setPosX(float X);
    void setPosY(float Y);
    void setInventarioItemsIDs(const int inventarioItemsIDs[30]);
    void setNombreDireccionTextura(std::string nombreDireccionTextura);
    void setAbierto(bool nuevoEstado);
    void setPosicionEscondite(float X, float Y);
    void setPosicionAbierto(float X, float Y);


    /// Otros Metodos
    //void actualizar(sf::Vector2f posGlobalDelMouse, sf::Mouse mouse);
    void update(const sf::Vector2f& posGlobalDelMouse, const sf::Mouse& mouse, const sf::View& vista, const float& relacionAspecto);
    void cargarVectorIDs(int vectorIDs[30]);
    void copiarVectorDeIDs(int vectorAlmacen[30]);
    bool agregarItem(int ID, int cantidad = 1);
    bool quitarItem(int ID, int cantidad = 1);
    int buscarItems(int ID, int cantidad = 1);
    void copiarVectorDeCantidades(int vectorAlmacen[30]);
    void cargarVectorCantidades(int vectorCantidades[30]);
    Item* obtenerPunteroInventario();

    void controlAbrirCerrarInventario(sf::Event& evento);

};
