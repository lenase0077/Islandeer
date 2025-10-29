//#include <iostream>
//#include "Enemigo.h"
//using namespace std;
//
////Enemigo::Enemigo()
////: _velocidad(0,0)
////{
////    setPosition(rand() % 500 , rand() % 500);
////    _sprite.setPosition(0,0);
////    _sprite.setTextureRect(sf::IntRect(0,0,16,16));
////    _colision.setID("Enemy");
////    _colision.setColision(getColisionBounds());
////}
//
//void Enemigo::draw(sf::RenderTarget& target, sf::RenderStates states) const
//{
//
//    states.transform *= getTransform();
//    target.draw(_sprite, states);
//}
//
//
//
//
//
//sf::Vector2f Enemigo::getPosition(){
//    return sf::Transformable::getPosition();
//}
//
//sf::FloatRect Enemigo::getColisionBounds() const {
//
//    sf::FloatRect localRect = _sprite.getLocalBounds();
//
//    return getTransform().transformRect(localRect);
//}
