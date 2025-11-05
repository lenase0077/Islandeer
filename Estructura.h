#pragma once
#include "SFML/Graphics.hpp"
#include "Colisionador.h"
#include <list>
#include <vector>
#include "Loot.h"

class Estructura : public sf::Transformable, public sf::Drawable
{
private:
    float _vida;
    int _bloqueID;
    Colisionador _colision;
    sf::Sprite _sprite;
    sf::Texture _textura;
    std::vector<int> _lootsIDs;
public:
    Estructura( sf::Texture& texturaBloques, float posX, float posY, int id);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void setVida(float nuevaVida);
    void setLootsIDs(const std::vector<int>& nuevoLootsIDs);

    void recibirGolpe(float danio);
    Colisionador &getColisionador() {return _colision;};
    bool estaDestruido() const;
    ~Estructura(){};
    void liberarLoot(sf::Texture& texturaItems,std::list<Loot>& listaLoot);
};
