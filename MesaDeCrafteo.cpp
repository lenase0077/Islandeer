#include "MesaDeCrafteo.h"
#include "Comando.h"
#include <cmath>
#include <iostream>
using namespace std;

MesaDeCrafteo::MesaDeCrafteo( sf::Texture& texturaBloques, sf::Texture& texturaUI, float posX, float posY, int id) :
    Estructura (texturaBloques,posX,posY,id)
{

    ///NOTA: a modo de prueba y para no afectar el funcionamiento de los otros herederos de la calse estructura creare la fabrica de items aqui, SOLO ES TEMPORAL

    _items[0]  = _fabItems.crearItem(0);//Pico piedra
    _items[1]  = _fabItems.crearItem(1);//Pico Hierro
    _items[2]  = _fabItems.crearItem(2);//Pico Diamante
    _items[3]  = _fabItems.crearItem(3);//Hacha piedra
    _items[4]  = _fabItems.crearItem(4);//Hacha Hierro
    _items[5]  = _fabItems.crearItem(5);//Hacha Diamante
    _items[6]  = _fabItems.crearItem(24);//Cuchillo obsidiana
    _items[7]  = _fabItems.crearItem(28);//Balde
    _items[8]  = _fabItems.crearItem(14);//Soga
    _items[9]  = _fabItems.crearItem(6);//Espada piedra
    _items[10] = _fabItems.crearItem(7);//Espada Hierro
    _items[11] = _fabItems.crearItem(8);//Espada Diamante
    _items[12] = _fabItems.crearItem(9);//Arco
    _items[13] = _fabItems.crearItem(15);//Flecha
    _items[14] = _fabItems.crearItem(52);//Mesa de crafteo
    _items[15] = _fabItems.crearItem(50);//Horno
    _items[16] = _fabItems.crearItem(49);//Cofre
    _items[17] = _fabItems.crearItem(51);//Valla
    _items[18] = _fabItems.crearItem(16);//Antorcha
    _items[19] = _fabItems.crearItem(53);//Mate

    //Pico piedra
    agregarItemRequerido( 0, 18, 3); // piedra x3
    agregarItemRequerido( 0, 10, 1); // palo x1
    agregarItemRequerido( 0, 14, 1); // soga x1

    //Pico Hierro
    agregarItemRequerido( 1, 20, 3); // hierro x3
    agregarItemRequerido( 1, 10, 1); // palo x1

    //Pico Diamante
    agregarItemRequerido( 2, 22, 3); // diamante x3
    agregarItemRequerido( 2, 10, 1); // palo x1

    //Hacha piedra
    agregarItemRequerido( 3, 18, 3); // piedra x3
    agregarItemRequerido( 3, 10, 1); // palo x1
    agregarItemRequerido( 3, 14, 1); // soga x1

    //Hacha Hierro
    agregarItemRequerido( 4, 20, 3); // hierro x3
    agregarItemRequerido( 4, 10, 1); // palo x1

    //Hacha Diamante
    agregarItemRequerido( 5, 22, 3); // diamante x3
    agregarItemRequerido( 5, 10, 1); // palo x1

    //Cuchillo obsidiana
    agregarItemRequerido( 6, 23, 1); // obsidiana x1
    agregarItemRequerido( 6, 10, 1); // palo x1

    //Balde
    agregarItemRequerido( 7, 20, 3); // hierro x3

    //Soga
    agregarItemRequerido( 8, 37, 5); // Paja x5

    //Espada piedra
    agregarItemRequerido( 9, 18, 2); // piedra x2
    agregarItemRequerido( 9, 10, 1); // palo x1

    //Espada Hierro
    agregarItemRequerido( 10, 20, 2); // hierro x2
    agregarItemRequerido( 10, 10, 1); // palo x1

    //Espada Diamante
    agregarItemRequerido( 11, 22, 2); // diamante x2
    agregarItemRequerido( 11, 10, 1); // palo x1

    //Arco
    agregarItemRequerido( 12, 10, 3); // palo x3
    agregarItemRequerido( 12, 14, 3); // soga x3

    //Flecha
    agregarItemRequerido( 13, 10, 1); // palo x1
    agregarItemRequerido( 13, 20, 1); // hierro x1
    agregarItemRequerido( 13, 13, 1); // pluma x1

    //Mesa de crafteo
    agregarItemRequerido( 14, 10, 4); // palo x4
    agregarItemRequerido( 14, 20, 4); // hierro x4

    //Horno
    agregarItemRequerido( 15, 18, 8); // piedra x8

    //Cofre
    agregarItemRequerido( 16, 10, 8); // palo x8

    //Valla
    agregarItemRequerido( 17, 10, 4); // palo x4
    agregarItemRequerido( 17, 14, 1); // soga x1

    //Antorcha
    agregarItemRequerido( 18, 10, 1); // palo x1
    agregarItemRequerido( 18, 19, 1); // carbon x1

    //Mate
    agregarItemRequerido( 19, 10, 1); // coco x1
    agregarItemRequerido( 19, 20, 1); // hierro x1
    agregarItemRequerido( 19, 27, 1); // yerba mate x1

    _sprFondoMesa.setTexture(texturaUI);
    _sprFondoMesa.setOrigin(0,0);
}


void MesaDeCrafteo::update(const sf::Vector2f& posicionJugador, const sf::Vector2f& posGlobalDelMouse, const sf::Mouse& mouse, const sf::View& vista, const float& relacionAspecto, InventarioInterfaz& inventario, float deltatime)
{
    ///Detectar jugador cercano
    float distanciaJugador = sqrt(pow(posicionJugador.x - getPosition().x,2) + pow(posicionJugador.y - getPosition().y,2));


    if (distanciaJugador < 40)
    {
        _sprite.setColor(sf::Color::Blue);
        _enUso = true;
    }
    else
    {
        _sprite.setColor(sf::Color::White);
        _enUso = false;
    }

    ///Adaptar UI a pantalla
    ajustarEscalaAutomaticamente(vista, relacionAspecto);

    controlDeItems(posGlobalDelMouse,inventario);
    ///Controlar selectores
    /***
    Para hacer eso:
        Dibujare los items crafteables y selectoros (semejante al inventario).
        los items describiran su uso y materiales nesesarios.
    */

    ///Verificar, quitar y dar items.

}

void MesaDeCrafteo::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(_sprite, states);
    if (_enUso)
    {
        target.draw(_sprFondoMesa);
        for(int i = 0; i < 20; i++)
        {
            ///DEBUG
            //target.draw(_selectoresDibujo[i]);

            target.draw(*_items[i]);
        }
    }

}

// Ajusta escala y posicion del inventario segun la vista de camara
void MesaDeCrafteo::ajustarEscalaAutomaticamente(const sf::View& vista, const float& relacionAspecto)
{
    // Escala proporcional al tamanio de la vista
    sf::Vector2f escalaCartel(sf::Vector2f(vista.getSize().x/512, vista.getSize().y/512 * relacionAspecto));

    float centroX = ((_sprFondoMesa.getGlobalBounds().width/ 2) +66) * escalaCartel.x;

    // Calcula posiciones
    sf::Vector2f posicionCartel(vista.getCenter().x - centroX, vista.getCenter().y - vista.getSize().y/2);
    _sprFondoMesa.setPosition(posicionCartel);
    _sprFondoMesa.setScale(escalaCartel);


    //Calculamos posicion y ubicacion de selectores:
    int fila, columna, espaciadoIzquiera, espaciadoSuperior;
    float x1, x2, y1, y2;
    for(int i = 0; i < 20; i++)
    {

        fila = i / 10;
        columna = i % 10;
        espaciadoIzquiera = 2 * escalaCartel.x;
        espaciadoSuperior = 28 * escalaCartel.y;

        x1 = posicionCartel.x + espaciadoIzquiera + (columna * 32 * escalaCartel.x);
        x2 = posicionCartel.x + espaciadoIzquiera + ((columna+1) * 32 * escalaCartel.x);
        y1 = posicionCartel.y + espaciadoSuperior + (fila * 32 * escalaCartel.y);
        y2 = posicionCartel.y + espaciadoSuperior + ((fila + 1) * 32 * escalaCartel.y);

        //DEBUG
        _selectoresDibujo[i].setPosition(x1, y1);
        _selectoresDibujo[i].setSize({32.0, 32.0});
        _selectoresDibujo[i].setScale(escalaCartel.x, escalaCartel.y);
        _selectoresDibujo[i].setFillColor(sf::Color::Transparent);
        _selectoresDibujo[i].setOutlineColor(sf::Color::White);
        _selectoresDibujo[i].setOutlineThickness(0.5);

        //SELECTORES
        _selectores[i].set_dimenciones( x1, x2, y1, y2);



        _items[i] -> setPosition( x1 + (escalaCartel.x * 16), y1 + (escalaCartel.y * 16));
        _items[i] -> setScale(escalaCartel.x, escalaCartel.y);

    }
}

///CREAR LA FUNCION controlDeItems

void MesaDeCrafteo::controlDeItems(const sf::Vector2f& posGlobalDelMouse, InventarioInterfaz& inventario)
{
    Comandos& input = Comandos::getInstancia();


    for(int i = 0; i < 20; i++)
    {
        if(!recursosExistentes( i, inventario))
        {
            _items[i] -> setColor(sf::Color(255,255,255,50));
        }
        else
        {
            _items[i] -> setColor(sf::Color(255,255,255,255));

            if (_selectores[i].estaDentro(posGlobalDelMouse.x,posGlobalDelMouse.y,true))
            {
                ///Modificar la escala del item seleccionado
                _items[i] -> setScale(_items[i] -> getScale().x  * 1.2, _items[i] -> getScale().y * 1.2);
                if(input.mouseIzqRecienPresionado){
                    quitarRecursosNecesarios( i, inventario);
                    inventario.agregarItem(_items[i] -> getID(), 1);
                }
            }
        }
    }
}

void MesaDeCrafteo::agregarItemRequerido(int numeroItem, int idItemRequerido, int cantidadItemRequerido)
{
    const int ID_ITEM_REQUERIDO = 0;
    const int CANT_ITEM_REQUERIDO = 1;

    _requisitosCrafteo[numeroItem][ID_ITEM_REQUERIDO].push_back(idItemRequerido);
    _requisitosCrafteo[numeroItem][CANT_ITEM_REQUERIDO].push_back(cantidadItemRequerido);
}

bool MesaDeCrafteo::recursosExistentes(int numeroItem, InventarioInterfaz& inventario)
{
    const int ID_ITEM_REQUERIDO = 0;
    const int CANT_ITEM_REQUERIDO = 1;

    for (size_t it = 0; it < _requisitosCrafteo[numeroItem][ID_ITEM_REQUERIDO].size(); it++)
    {

        int IDaBuscar = _requisitosCrafteo[numeroItem][ID_ITEM_REQUERIDO][it];
        int Cantidad  = _requisitosCrafteo[numeroItem][CANT_ITEM_REQUERIDO][it];

        if (inventario.buscarItems( IDaBuscar, Cantidad) == -1)
        {
            return false;
        }
    }
    return true;
}

void MesaDeCrafteo::quitarRecursosNecesarios(int numeroItem, InventarioInterfaz& inventario){
    const int ID_ITEM_REQUERIDO = 0;
    const int CANT_ITEM_REQUERIDO = 1;

    for (size_t it = 0; it < _requisitosCrafteo[numeroItem][ID_ITEM_REQUERIDO].size(); it++)
    {

        int IDaBuscar = _requisitosCrafteo[numeroItem][ID_ITEM_REQUERIDO][it];
        int Cantidad  = _requisitosCrafteo[numeroItem][CANT_ITEM_REQUERIDO][it];

        inventario.quitarItem( IDaBuscar, Cantidad);
    }
}


