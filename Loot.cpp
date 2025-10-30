#include "Loot.h"
#include "cmath"


using namespace std;

Loot::Loot(const sf::Vector2f& posicion, const int& id, const int& cantidad){
    setPosicion(posicion);
    _item.setID(id);
    _item.actualizarSprite();
    _item.setCantidad(1);//Hacemos esto para que no sea visible el numero cantidad.
    _cantidad = cantidad;

    ///Definimos dimenciones de Colicionador
  /*  sf::FloatRect dimencionColision();
    _colisionConJugador.setColision(dimencionColision);*/
}

///HACER GET y SET de _cantidad

void Loot::setPosicion(sf::Vector2f posicion){
    setPosition(posicion);
}

void Loot::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    states.transform *= getTransform();
    target.draw(_item,states);
}

void Loot::update(){
    _incrementoSeno += 0.05;
    setPosition(getPosition().x, getPosition().y + (sin(_incrementoSeno))* 0.1);
    setScale(sin(_incrementoSeno) * 1, getScale().y);
}
