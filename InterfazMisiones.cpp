#include "InterfazMisiones.h"
#include "funcionesInterpolacion.h"

InterfazMisiones::InterfazMisiones( sf::Font& fuenteTextos, sf::Texture& texturaMision){
    _fuenteTextos = &fuenteTextos;
    _texturaMision = &texturaMision;
    _sprBotonAbrir.setTexture(*_texturaMision);
    _sprBotonAbrir.setTextureRect({256,16,32,32});
    _sprBotonAbrir.setOrigin(16,16);
    _sprBotonAbrir.setPosition(26,26);
}


void InterfazMisiones::update(const sf::Vector2f& posGlobalDelMouse, InventarioInterfaz& inventarioJugador, int& monedasJugador){

    sf::Vector2f escalaActualBoton =  _sprBotonAbrir.getScale();

    Comandos& input = Comandos::getInstancia();

    if (_botonAbrir.estaDentro(posGlobalDelMouse.x,posGlobalDelMouse.y, true)){
        lerp(escalaActualBoton, {1.1,1.1}, 0.2);
        _sprBotonAbrir.setScale(escalaActualBoton);
        _sprBotonAbrir.setColor(sf::Color(255,255,255,255));
        if (input.mouseIzqRecienPresionado){
            if (_oculto == true) _oculto = false;
            else _oculto = true;
        }
    }
    else{
        lerp(escalaActualBoton, {1,1}, 0.2);
        _sprBotonAbrir.setScale(escalaActualBoton);
        _sprBotonAbrir.setColor(sf::Color(255,255,255,50));
    }

    for(int i = 0; i < _misiones.size(); i++){
        _misiones[i].update(posGlobalDelMouse, inventarioJugador, monedasJugador);

        if(_misiones[i].getReclamado()) _misiones.erase(_misiones.begin() + i);
    }
}

void InterfazMisiones::agregarMision(const std::string& titulo,
                                     const std::string& explicacion,
                                     const int& recompensa,
                                     std::vector<int> itemsRequeridosIDs,
                                     std::vector<int> itemsRequeridosCantidad)
{
    MisionGUI misionAgregada = MisionGUI(*_fuenteTextos, *_texturaMision, titulo, explicacion, recompensa);

    misionAgregada.setItemsRequeridos(itemsRequeridosIDs,itemsRequeridosCantidad);

    _misiones.push_back(misionAgregada);
}

void InterfazMisiones::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    states.transform *= getTransform();
    for(int i = 0; i < _misiones.size(); i++){
        target.draw(_misiones[i]);
    }
    target.draw(_sprBotonAbrir,states);
}

void InterfazMisiones::ajustarEscalaAutomaticamente(const sf::View& vista, const float& relacionAspecto){

    // Escala proporcional al tamanio de la vista
    sf::Vector2f escalaCartel(sf::Vector2f(vista.getSize().x/512, vista.getSize().y/512 * relacionAspecto));

    // Calcula posiciones

    sf::Vector2f posicionCartel;

    float posX = vista.getCenter().x - vista.getSize().x/2;
    float posY = vista.getCenter().y - vista.getSize().y/2;

    ///SETEADO DEL TRANSFORM
    setPosition(posX,posY);
    setScale(escalaCartel);

    int botonAbrirX1 = getPosition().x + 10 * getScale().x;
    int botonAbrirX2 = getPosition().x + 42 * getScale().x;
    int botonAbrirY1 = getPosition().y + 10 * getScale().y;
    int botonAbrirY2 = getPosition().y + 42 * getScale().y;

    /*
    _sprBotonAbrir.setOrigin(16,16);
    _sprBotonAbrir.setPosition(26,26);
    */

    _botonAbrir.set_dimenciones(botonAbrirX1,botonAbrirX2,botonAbrirY1,botonAbrirY2);


    for(int i = 0; i < _misiones.size(); i++){
        _misiones[i].setOculto(_oculto);
        _misiones[i].setReglon(i);
        _misiones[i].ajustarEscalaAutomaticamente(vista, relacionAspecto);
    }
}
