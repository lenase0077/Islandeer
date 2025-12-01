#pragma once
#include "SeleccionRectangulo.h"
#include "Item.h"
#include "ItemDescripcion.h"
#include "Loot.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <list>
#include "FabricaItems.h"
#include "json.hpp"
#include <memory>
#include <utility>
#include <array>
#include "Comando.h"

class InventarioResumido;

class InventarioInterfaz : public sf::Drawable, sf::Transformable
{
private:

    bool _primerVuelta = false;
    bool _abierto = false;

    int _indiceUltimoItemAnalizado = 100;
    float _posX, _posY;
    sf::Vector2f _posicionEscondite;
    sf::Vector2f _posicionAbierto;
    ItemDescripcion _descripcion;

    std::array<std::unique_ptr<Item>, 30> _inventarioItems;
    std::unique_ptr<Item> _itemEnMano;
    std::unique_ptr<Item>* _ptrItemEnManoActual; // NUEVO: Este puntero apuntar  a _itemEnMano (propio) o al de otro inventario

    FabricaItems* _fabItems;
    std::array<SeleccionRectangulo, 30> _areasSeleccion;
    std::string _nombreDireccionTextura;
    sf::Texture _texturaFondo;
    sf::Sprite _sprFondoInventario;

    InventarioResumido* _inventarioResumido = nullptr;

    ///Metodos privados
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    std::unique_ptr<Item> clonarItem(const Item* item) const;
    bool sumarItems(std::unique_ptr<Item>& ItemIncrementador, std::unique_ptr<Item>& ItemIncrementado);
    void ajustarEscalaAutomaticamente(const sf::View& vista, const float& relacionAspecto);
    void soltarLoot(std::unique_ptr<Item>& itemQueTirar, std::list<Loot>& listaLoots, bool tirarCompleto = false);

public:
    /// Constructores
    InventarioInterfaz(FabricaItems& fabItems,std::string nombreDireccionTextura = "Inventario.png");
    InventarioInterfaz(){};

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
    void setNombreDireccionTextura(std::string nombreDireccionTextura);
    void setAbierto(bool nuevoEstado);
    void setPosicionEscondite(float X, float Y);
    void setPosicionAbierto(float X, float Y);

    /// Otros Metodos
    void update(const sf::Vector2f& posGlobalDelMouse, const sf::View& vista, const float& relacionAspecto, std::list<Loot>& listaLoots);
    void controlDeEventos(sf::Event& evento);
    void cargarVectorIDs(int vectorIDs[30]);
    void copiarVectorDeIDs(int vectorAlmacen[30]);
    bool agregarItem(int ID, int cantidad = 1);
    bool quitarItem(int ID, int cantidad = 1);
    int buscarItems(int ID, int cantidad = 1);
    void copiarVectorDeCantidades(int vectorAlmacen[30]);
    void cargarVectorCantidades(int vectorCantidades[30]);

    void copiarItemsEnVector(Item* vectorDestino[30]);

    void setInventarioResumido(InventarioResumido* InvR);
    InventarioResumido* getInventarioResumido();
    void consumirItemEnSlot(int slot, int cantidad);
    Item* getItemEnMano();


    std::unique_ptr<Item>* obtenerPunteroItemEnMano();// M‚todo para obtener la direcci¢n de memoria de TU item en mano

    void enlazarItemEnMano(std::unique_ptr<Item>* punteroExterno);// M‚todo para decirle a este inventario que use el item en mano de otro

    bool usaItemEnManoExterno();// Para saber si estamos usando el item en mano de otro inventario (principalmente usado en draw)
};
