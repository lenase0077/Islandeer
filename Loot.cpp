#include "Loot.h"
#include "cmath"
#include "funcionesInterpolacion.h"


using namespace std;

Loot::Loot(sf::Texture& texturaItems,const sf::Vector2f& posicion, const int& id)
{
    setPosicion(posicion);
    Item item(texturaItems,id);
    _item = item;
    _item.actualizarSprite();
    _item.setCantidad(1);//Hacemos esto para que no sea visible el numero cantidad.
}

///HACER GET y SET de _cantidad

void Loot::setPosicion(sf::Vector2f posicion)
{
    setPosition(posicion);
}

void Loot::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(_item,states);
}

void Loot::update(const sf::Vector2f posicionJugador, InventarioInterfaz& inventario)
{
    if (!_looted)
    {
        ///Efecto animacion
        _incrementoSeno += 0.05;
        setPosition(getPosition().x, getPosition().y + (sin(_incrementoSeno))* 0.1);
        setScale(sin(_incrementoSeno) * 1, getScale().y);



        float distancia = sqrt(pow(posicionJugador.x - getPosition().x,2) + pow(posicionJugador.y - getPosition().y,2));
        if (distancia < 32)
        {
            sf::Vector2f posicionActual = getPosition();
            float nuevaPosX = getPosition().x + ((posicionJugador.x - getPosition().x)*0.05);
            float nuevaPosY = getPosition().y + ((posicionJugador.y - getPosition().y)*0.05);
            setPosition( nuevaPosX, nuevaPosY);

            ///chocar con jugador
            if (distancia < 8)
            {
                if (inventario.agregarItem(_item.getID(),1)) _looted = true;
            }
        }

    }
}

bool Loot::getLooted(){
    return _looted;
}
