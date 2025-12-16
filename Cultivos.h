#pragma once
#include <SFML/Graphics.hpp>
#include "FabricaItems.h"
#include "Loot.h"
#include <list>

class cultivo : public sf::Drawable, public sf::Transformable
{
private:
    sf::Sprite _sprite;
    int _faseDeCrecimiento;
    float _tiempoAcumulado;
    float _tiempoParaCrecer;
    int _tipoCultivo;
    bool _listoParaCosechar;
    int _idProducto;
    int _idSemilla;

public:
    cultivo(sf::Texture& textura, float x, float y, int filaSprite, int idProducto, int idSemilla);
    void update (float deltaTime);
    bool intentarCosechar (std::list<Loot>& listaLoots, FabricaItems& fabrica);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::FloatRect getBounds() const;
    bool estaMaduro() const;
};
