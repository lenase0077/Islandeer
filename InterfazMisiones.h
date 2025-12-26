#pragma once
#include "MisionGUI.h"
#include <vector>
#include "InventarioIntefaz.h"

class InterfazMisiones : public sf::Transformable, public sf::Drawable
{
private:
    std::vector<MisionGUI> _misiones;
    bool _oculto = false;
public:
    InterfazMisiones(const sf::Font& fuenteTextos, const sf::Texture& texturaMision);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void agregarMision(const std::string& titulo = "TITULO MISION",
                       const std::string& explicacion = "Aqui va la explicacion de la mision a realizar",
                       const int& recompensa = 1,
                       std::vector<int> itemsRequeridosIDs = {},
                       std::vector<int> itemsRequeridosCantidad = {});
    void update(const sf::Vector2f& posGlobalDelMouse, InventarioInterfaz& inventarioJugador, int& monedasJugador);
    void ajustarEscalaAutomaticamente(const sf::View& vista, const float& relacionAspecto);
};


