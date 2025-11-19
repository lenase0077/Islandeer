#pragma once
#include "SFML/Graphics.hpp"
#include "Colisionador.h"
#include <list>
#include <vector>
#include "Loot.h"
#include "FabricaItems.h"

class Estructura : public sf::Transformable, public sf::Drawable
{
private:
    float _vida;
    int _bloqueID;
    Colisionador _colision;
    std::vector<int> _lootsIDs;
public:
    sf::Sprite _sprite;
    Estructura( sf::Texture& texturaBloques, float posX, float posY, int id);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void setVida(float nuevaVida);
    void setLootsIDs(const std::vector<int>& nuevoLootsIDs);

    virtual void update(const sf::Vector2f& posicionJugador, const sf::Vector2f& posGlobalDelMouse, const sf::Mouse& mouse, const sf::View& vista, const float& relacionAspecto, InventarioInterfaz& inventario);

    void recibirGolpe(float danio);
    Colisionador &getColisionador() {return _colision;};
    bool estaDestruido() const;
    ~Estructura(){};
    void liberarLoot(FabricaItems& fabItems,std::list<Loot>& listaLoot);
};
