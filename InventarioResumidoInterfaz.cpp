#include "InventarioResumidoInterfaz.h"
#include <iostream>

using namespace std;

///CONSTRUCTORES
InventarioResumido::InventarioResumido(sf::Texture& textura) ///Este Setter se usara principalmente por el InventarioInterfaz
{
    setSlotSeleccionado(0);
    _sprFondo.setTexture(textura);

    ///Configuracion Rectangulo Slot Seleccion
    _rectanguloSlotSeleccionado.setFillColor(sf::Color::Transparent);
    _rectanguloSlotSeleccionado.setOutlineThickness(0.8);
    _rectanguloSlotSeleccionado.setOutlineColor(sf::Color::Green);
    _rectanguloSlotSeleccionado.setSize(sf::Vector2f(32.f,32.f));

    if(!_fuenteTextoTitulo.loadFromFile("PIXEARG_.TTF")){
        cout << "ERROR AL CARGAR PIXEARG_.TTF" << endl;
    }

    ///Configuracion Titulo Seleccion
    _textoTitulo.setFont(_fuenteTextoTitulo);
    _textoTitulo.setFillColor(sf::Color::White);
    _textoTitulo.setOutlineThickness(1);
    _textoTitulo.setOutlineColor(sf::Color::Black);
    _textoTitulo.setCharacterSize(10);

    _textoTitulo.setStyle(sf::Text::Regular);

    sf::Texture& texture = const_cast<sf::Texture&>(_fuenteTextoTitulo.getTexture(10));
    texture.setSmooth(false);

}

///SETTERS
void InventarioResumido::setItems( Item vectorItems[]) ///Este Setter se usara principalmente por el InventarioInterfaz
{
    for (int i = 0; i < 10; i++){
        _items[i] = vectorItems[i];
    }
}

void InventarioResumido::setSlotSeleccionado(int slot)
{
    ///Lo mantenemos en un rango (0-9)
    if (slot < 0) slot = 0;
    else if (slot > 9) slot = 9;
    _slotSeleccionado = slot;
}

void InventarioResumido::setPosicion(float x, float y){
    setPosition(x,y);
}

void InventarioResumido::setEscala(float escalaX, float escalaY){
    setScale(escalaX,escalaY);
}

///GETTERS
int InventarioResumido::getSlotSeleccionado()
{
    return _slotSeleccionado;
}
Item InventarioResumido::getItem(int slot)
{
    return _items[slot];
}

///OTROS METODOS
void InventarioResumido::cambiarSlotsConEventos(sf::Event& evento)
{
    ///CAMBIAR SLOT CON TECLAS
    if (evento.type == sf::Event::KeyPressed){
            switch (evento.key.code){
                case sf::Keyboard::Num1:
                    setSlotSeleccionado(0);
                    break;
                    case sf::Keyboard::Num2:
                    setSlotSeleccionado(1);
                    break;
                    case sf::Keyboard::Num3:
                    setSlotSeleccionado(2);
                    break;
                    case sf::Keyboard::Num4:
                    setSlotSeleccionado(3);
                    break;
                    case sf::Keyboard::Num5:
                    setSlotSeleccionado(4);
                    break;
                    case sf::Keyboard::Num6:
                    setSlotSeleccionado(5);
                    break;
                    case sf::Keyboard::Num7:
                    setSlotSeleccionado(6);
                    break;
                    case sf::Keyboard::Num8:
                    setSlotSeleccionado(7);
                    break;
                    case sf::Keyboard::Num9:
                    setSlotSeleccionado(8);
                    break;
                    case sf::Keyboard::Num0:
                    setSlotSeleccionado(9);
                    break;
                    default:
                    break;
            }
    }
    ///CAMBIAR SLOT CON RUEDA
    else if (evento.type == sf::Event::MouseWheelScrolled){
        if (evento.mouseWheelScroll.delta < 0){
            if (getSlotSeleccionado() == 9) setSlotSeleccionado(0);
            else setSlotSeleccionado(getSlotSeleccionado()+1);
        }
        else{
            if (getSlotSeleccionado() == 0) setSlotSeleccionado(9);
            else setSlotSeleccionado(getSlotSeleccionado()-1);
        }
    }
}

void InventarioResumido::update(const sf::View& vista, const float& relacionAspecto){

    setScale(vista.getSize().x/512, vista.getSize().y/512*relacionAspecto);
    setPosition(vista.getCenter().x-(_sprFondo.getGlobalBounds().width * getScale().x)/2,vista.getCenter().y+(vista.getSize().y/3));

    _rectanguloSlotSeleccionado.setPosition(_slotSeleccionado*32,0);

    for (int i = 0; i < 10; i++){
        _items[i].setPosition(16 + i*32,16);
    }

    if (_items[getSlotSeleccionado()].getID() != -1){
        _textoTitulo.setString(_items[getSlotSeleccionado()].getTitulo());
    }
    else{
        _textoTitulo.setString("");
    }
    _textoTitulo.setOrigin(_textoTitulo.getGlobalBounds().width/2,_textoTitulo.getGlobalBounds().height/2);
    _textoTitulo.setPosition(_sprFondo.getGlobalBounds().width/2,-16);
}

void InventarioResumido::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    states.transform *= getTransform();
    target.draw(_sprFondo,states);

    target.draw(_rectanguloSlotSeleccionado,states);
    for (int i = 0; i < 10; i++){
        if (_items[i].getID() != -1) target.draw(_items[i],states);
    }
    target.draw(_textoTitulo,states);
}


