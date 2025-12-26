#include "InterfazMisiones.h"
InterfazMisiones::InterfazMisiones(const sf::Font& fuenteTextos, const sf::Texture& texturaMision){

}


void InterfazMisiones::update(const sf::Vector2f& posGlobalDelMouse, InventarioInterfaz& inventarioJugador, int& monedasJugador){

}

void InterfazMisiones::agregarMision(const std::string& titulo,
                                     const std::string& explicacion,
                                     const int& recompensa,
                                     std::vector<int> itemsRequeridosIDs,
                                     std::vector<int> itemsRequeridosCantidad)
{
    /**
    Pasos a seguir:
    - usar push_back para agregar las misiones.
    - ajustar las coordenadas Y de los mismos dependiendo su indice y quizas la rueda del mause.
    - al completarlo eliminar la mision.
    */
}

void InterfazMisiones::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    states.transform *= getTransform();
}

void InterfazMisiones::ajustarEscalaAutomaticamente(const sf::View& vista, const float& relacionAspecto){

}
