//#include "Movimiento_IA.h"
//
//
//
//void MovimientoIA::Perseguir(sf::Vector2f Posicionpersonaje, sf::Vector2f PosicionEnemigo){
//
//
//    sf::Vector2f Direccion = Posicionpersonaje - PosicionEnemigo;
//
//    float longitud = std::sqrt(Direccion.x * Direccion.x + Direccion.y * Direccion.y);
//    float velocidad = 1.0;
//
//    if (longitud > 1){
//        Direccion.x /= longitud;
//        Direccion.y /= longitud;
//
//        _velocidad.x = Direccion.x * velocidad;
//        _velocidad.y = Direccion.y * velocidad;
//    }
//    else{
//        _velocidad = {0 , 0};
//    }
//
//}
//
//
//void MovimientoIA::Update(sf::Vector2f enemigo){
//
//    Perseguir(enemigo);
//    move(_velocidad);
//    _colision.setColision(getColisionBounds());
//}
