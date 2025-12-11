#pragma once
#include "Estructura.h"
#include "SeleccionRectangulo.h"
#include "InventarioIntefaz.h"
#include <memory>
#include "Item.h"
#include "FabricaItems.h"
#include <vector>

class MesaDeCrafteo : public Estructura
{
private:
    sf::Sprite _sprFondoMesa;
    SeleccionRectangulo _selectores[20];
    std::unique_ptr<Item> _items[20];
    std::vector<int> _requisitosCrafteo[20][2];
    bool recursosExistentes(int numeroItem, InventarioInterfaz& inventario);
    FabricaItems _fabItems;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    bool _enUso = false;

    ///DEBUG
    sf::RectangleShape _selectoresDibujo[20];

    ///Metodos privados
    void agregarItemRequerido(int numeroItem, int idItemRequerido, int cantidadItemRequerido);
    void quitarRecursosNecesarios(int numeroItem, InventarioInterfaz& inventario);

public:
    void update(const sf::Vector2f& posicionJugador, const sf::Vector2f& posGlobalDelMouse, const sf::Mouse& mouse, const sf::View& vista, const float& relacionAspecto, InventarioInterfaz& inventario, float deltatime);
    MesaDeCrafteo(sf::Texture& texturaBloques, sf::Texture& texturaUI, float posX, float posY, int id);
    void ajustarEscalaAutomaticamente(const sf::View& vista, const float& relacionAspecto);
    void controlDeItems(const sf::Vector2f& posGlobalDelMouse, InventarioInterfaz& inventario);

};

