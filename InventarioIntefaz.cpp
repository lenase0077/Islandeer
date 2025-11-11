#include "InventarioIntefaz.h"
#include "funcionesInterpolacion.h"
#include "cmath"

using namespace std;

///CONSTRUCTORES
//{
InventarioInterfaz::InventarioInterfaz(sf::Texture& texturaItems, std::string nombreDireccionTextura)
{
    setNombreDireccionTextura("Inventario.png");

    _texturaFondo.loadFromFile(getNombreDireccionTextura());
    _sprFondoInventario.setTexture(_texturaFondo);
    _sprFondoInventario.setOrigin(sf::Vector2f(0,0));

    ///ACA ESTA EL MALDITO ERRRROORRR

    _texturaItems = &texturaItems;

    for(int i = 0; i<30; i++)
    {
        _inventarioItems[i].setID(-1);
        _inventarioItems[i].setCantidad(1);
        _inventarioItems[i].setTexture(texturaItems);
    }
}
//}
///GETTERS
//{
float InventarioInterfaz::getPosX()
{
    return _posX;
}
float InventarioInterfaz::getPosY()
{
    return _posY;
}

std::string InventarioInterfaz::getNombreDireccionTextura()
{
    return _nombreDireccionTextura;
}

bool InventarioInterfaz::getAbierto()
{
    return _abierto;
}

sf::Vector2f InventarioInterfaz::getPosicionEscondite()
{
    return _posicionEscondite;
}

sf::Vector2f InventarioInterfaz::getPosicionAbierto()
{
    return _posicionAbierto;
}

//}

///SETTERS
//{
void InventarioInterfaz::setPosX(float X)
{
    _posX = X;
}
void InventarioInterfaz::setPosY(float Y)
{
    _posY = Y;
}
void InventarioInterfaz::setNombreDireccionTextura(std::string nombreDireccionTextura)
{
    _nombreDireccionTextura = nombreDireccionTextura;
}
void InventarioInterfaz::setAbierto(bool nuevoEstado)
{
    _abierto = nuevoEstado;
}

void InventarioInterfaz::setPosicionEscondite(float X, float Y)
{
    _posicionEscondite = sf::Vector2f(X,Y);
}

void InventarioInterfaz::setPosicionAbierto(float X, float Y)
{
    _posicionAbierto = sf::Vector2f(X,Y);
}
//}


void InventarioInterfaz::update(const sf::Vector2f& posGlobalDelMouse, const sf::Mouse& mouse, const sf::View& vista, const float& relacionAspecto, std::list<Loot>& listaLoots, sf::Keyboard& tecladoEntrada)
{
    ajustarEscalaAutomaticamente(vista,relacionAspecto);

    ///habria que mover esto pa no generar todo el rato en actualizar (mover a atributos)
    bool izquierdoPresionadoActual = mouse.isButtonPressed(sf::Mouse::Left);
    bool izquierdoRecienPresionado = izquierdoPresionadoActual && !_izquierdoPresionadoAnterior;

    if (_timerDobleClick2.getElapsedTime().asMilliseconds() >= 250)
    {
        _contadorClicksIzquierdo = 0;
    }

    bool mouseInteractuo = false;

    ///LOGRAR LEER LOS MALDITOS SELECTORES
    for(int i = 0; i<30; i++)
    {
        int cantidadColumnas = 10;
        int columna = i % cantidadColumnas;
        int fila = i / cantidadColumnas;

        _areasSeleccion[i].set_dimenciones(getPosition().x+columna*32*getScale().x,getPosition().x+(columna+1)*32*getScale().x,getPosition().y+fila*32*getScale().y,getPosition().y+(fila+1)*32*getScale().y);

        if (_areasSeleccion[i].estaDentro(posGlobalDelMouse.x,posGlobalDelMouse.y, true))
        {
            ///Control objeto descripcion
            if(_inventarioItems[i].getID() != -1)
            {
                mouseInteractuo = true;
                _descripcion.setVisible(true);
                _descripcion.setTitulo(_inventarioItems[i].getTitulo());
                _descripcion.setDescripcion(_inventarioItems[i].getDescripcion());
                if  (i % 10 >= 5){
                    _descripcion.EstablecerPosicion((posGlobalDelMouse.x-getPosition().x-(150 * getScale().x))/getScale().x*2,(posGlobalDelMouse.y-getPosition().y)/getScale().y*2);
                }
                else{
                    _descripcion.EstablecerPosicion((posGlobalDelMouse.x-getPosition().x)/getScale().x*2,(posGlobalDelMouse.y-getPosition().y)/getScale().y*2);
                }
                _descripcion.ActualizarDimensiones();
            }

            ///Efecto Seleccion Suave
            sf::Vector2f escalaActual(_inventarioItems[i].getEscala());
            sf::Vector2f escalaObjetivo(1.25,1.25);
            lerp(escalaActual,escalaObjetivo,0.2);
            _inventarioItems[i].setEscala(escalaActual);

            ///==============================================================================
            ///==============================================================================
            ///                         CONTROL SOLTAR ITEMS CON LA Q
            if (!tecladoEntrada.isKeyPressed(sf::Keyboard::Q)){
                _frameActualQprecionada = false;
            }
            if (tecladoEntrada.isKeyPressed(sf::Keyboard::Q) && !_frameActualQprecionada){
                _frameActualQprecionada = true;
                soltarLoot(_inventarioItems[i], listaLoots);
            }
            ///
            ///==============================================================================
            ///==============================================================================
            if (!_clickDerechoDisponible && (!mouse.isButtonPressed(sf::Mouse::Right)))
            {
                _clickDerechoDisponible = true;
                _indiceUltimoItemAnalizado = 100;
            }


            if (mouse.isButtonPressed(sf::Mouse::Right) && _clickDerechoDisponible)
            {
                _contadorClicksIzquierdo = 0;
                _timerDobleClick2.restart();
                _clickDerechoDisponible = false;
                if (!_hayItemEnMano)   //Si no hay item en mano
                {
                    if (_inventarioItems[i].getID() != -1 && _inventarioItems[i].getCantidad() > 1)   //si hay un item en la celda seleccionada
                    {
                        _hayItemEnMano = true;
                        _itemEnMano = _inventarioItems[i];
                        int divicion = _inventarioItems[i].getCantidad()/2;
                        int resto = _inventarioItems[i].getCantidad()%2;

                        if (_inventarioItems[i].getCantidad()%2 != 0)
                        {
                            _itemEnMano.setCantidad(divicion);
                            _inventarioItems[i].setCantidad(divicion + resto);
                        }
                        else
                        {
                            _itemEnMano.setCantidad(divicion);
                            _inventarioItems[i].setCantidad(divicion);
                        }
                        _indiceUltimoItemAnalizado = i;
                    }
                }
                else     //Si hay Item en mano
                {
                    if (_inventarioItems[i].getID() != -1)   //No es un espacio vacio
                    {
                        if (_inventarioItems[i].getID() != _itemEnMano.getID())
                        {
                            _itemEnMano.setEscala(sf::Vector2f(1.3,1.3));
                            swap(_inventarioItems[i], _itemEnMano);
                        }
                    }
                }
            }

            if (mouse.isButtonPressed(sf::Mouse::Right) && i != _indiceUltimoItemAnalizado)
            {
                if(_hayItemEnMano)
                {
                    if (_inventarioItems[i].getID() != -1)
                    {
                        if (_inventarioItems[i].getID() == _itemEnMano.getID() && _inventarioItems[i].getCantidad() < _inventarioItems[i].getCantidadMax())
                        {
                            if (_itemEnMano.getCantidad()>1)
                            {
                                _itemEnMano.setCantidad(_itemEnMano.getCantidad()-1);
                                _inventarioItems[i].setCantidad(_inventarioItems[i].getCantidad()+1);
                                _indiceUltimoItemAnalizado = i;
                            }
                            else
                            {
                                _hayItemEnMano = false;
                                _inventarioItems[i].setCantidad(_inventarioItems[i].getCantidad()+1);
                                _itemEnMano.setID(-1);
                            }
                        }
                    }
                    else
                    {
                        _indiceUltimoItemAnalizado = i;
                        if (_itemEnMano.getCantidad() > 1)
                        {
                            _itemEnMano.setEscala(sf::Vector2f(1.3,1.3));
                            _inventarioItems[i] = _itemEnMano;
                            _inventarioItems[i].setCantidad(1);
                            _itemEnMano.setCantidad(_itemEnMano.getCantidad()-1);
                        }
                        else
                        {
                            _hayItemEnMano = false;
                            _itemEnMano.setEscala(sf::Vector2f(1.3,1.3));
                            _inventarioItems[i] = _itemEnMano;
                            _itemEnMano.setID(-1);
                        }
                    }
                }
            }



            if (izquierdoRecienPresionado)
            {


                if (_inventarioItems[i].getID() != -1 || _hayItemEnMano)
                {
                    _timerDobleClick2.restart();
                    _contadorClicksIzquierdo++;

                    if(!_hayItemEnMano)   //SI NO HAY ITEM EN MANO
                    {
                        if(_inventarioItems[i].getID() != -1)
                        {
                            _hayItemEnMano = true;
                            _itemEnMano = _inventarioItems[i];
                            _inventarioItems[i].setID(-1);
                        }
                    }
                    else     //SI HAY ITEM EN MANO
                    {

                        if (_inventarioItems[i].getID() == _itemEnMano.getID())
                        {
                            _hayItemEnMano = !sumarItems(_itemEnMano,_inventarioItems[i]);
                        }
                        else if (_inventarioItems[i].getID() != -1)
                        {
                            _contadorClicksIzquierdo = 0;
                            _hayItemEnMano = true;
                            _itemEnMano.setEscala(sf::Vector2f(1.3,1.3));
                            swap(_itemEnMano,_inventarioItems[i]);
                        }
                        else
                        {
                            _hayItemEnMano = false;
                            _inventarioItems[i].setID(_itemEnMano.getID());
                            _inventarioItems[i].setCantidad(_itemEnMano.getCantidad());
                            _itemEnMano.setID(-1);
                        }
                    }

                    if (_contadorClicksIzquierdo >= 2)
                    {
                        if(_hayItemEnMano)
                        {
                            if (_itemEnMano.getCantidad() < _itemEnMano.getCantidadMax())
                            {

                                std::vector<int> indices_slots_con_item; ///usamos VECTOR :D


                                for (int x = 0; x < 30; x++)
                                {
                                    if (_inventarioItems[x].getID() == _itemEnMano.getID())
                                    {


                                        indices_slots_con_item.push_back(x); ///Empujamos al vector las cosas
                                        if (_itemEnMano.getCantidad() == _itemEnMano.getCantidadMax()) break;
                                    }
                                }
                                ///aca trabajamos con el vector                                                         ///si ta vacio we es empty
                                while (_itemEnMano.getCantidad() < _itemEnMano.getCantidadMax() && !indices_slots_con_item.empty())
                                {

                                    ///tendria que mover esto a atributos pa no generarlas en el actualizar
                                    int indice_mas_chico = -1;
                                    int cantidad_minima = -1;
                                    int indice_en_vector = -1;
                                    ///quiza sea mas legible no usar uwu
                                    for (size_t uwu = 0; uwu < indices_slots_con_item.size(); ++uwu)
                                    {

                                        int indice_actual = indices_slots_con_item[uwu]; ///en donde estamos en el vector
                                        int cantidad_actual = _inventarioItems[indice_actual].getCantidad(); /// cuanto tiene en donde estamos

                                        // Si es el primero que encontramos o si es menor que el mínimo actual
                                        if (cantidad_actual > 0 && (cantidad_minima == -1 || cantidad_actual < cantidad_minima))
                                        {
                                            cantidad_minima = cantidad_actual;
                                            indice_mas_chico = indice_actual;
                                            indice_en_vector = uwu;// Guardamos la posición en el vector `indices_slots_con_item`
                                        }
                                    }

                                    if (indice_mas_chico == -1)
                                    {
                                        break;
                                    }

                                    ///sumamos por indice

                                    sumarItems(_inventarioItems[indice_mas_chico], _itemEnMano);
                                    if (_inventarioItems[indice_mas_chico].getID() == -1)
                                    {
                                        ///borramo      ///esto borra                   ///primera posicion
                                        indices_slots_con_item.erase(indices_slots_con_item.begin() + indice_en_vector);
                                    }

                                }

                            }
                            _contadorClicksIzquierdo = 0;
                        }
                    }
                }
            }
        }
        else
        {
            ///Efecto Deseleccion Suave
            sf::Vector2f escalaActual(_inventarioItems[i].getEscala());
            sf::Vector2f escalaObjetivo(1,1);
            lerp(escalaActual,escalaObjetivo,0.2);
            _inventarioItems[i].setEscala(escalaActual);
        }
        _inventarioItems[i].setPosition(16 + columna * 32, 16 + fila * 32);
        _inventarioItems[i].actualizarSprite();


    }

    _izquierdoPresionadoAnterior = izquierdoPresionadoActual;



    if (_hayItemEnMano)
    {
        _itemEnMano.setPosition(posGlobalDelMouse.x,posGlobalDelMouse.y);
        _itemEnMano.setEscala(sf::Vector2f(1.3*getScale().x,1.3*getScale().y));
        _itemEnMano.actualizarSprite();

        if (!mouseInteractuo){
            if (izquierdoRecienPresionado){
                _hayItemEnMano = false;
                soltarLoot(_itemEnMano,listaLoots,true);
            }
        }

    }

    if(!mouseInteractuo || _hayItemEnMano)
    {
        _descripcion.setVisible(false);
    }

}

Item* InventarioInterfaz::obtenerPunteroInventario()
{
    return _inventarioItems;
}

void InventarioInterfaz::copiarVectorDeIDs(int vectorAlmacen[30])
{
    for (int i = 0; i < 30; i++)
    {
        vectorAlmacen[i] = _inventarioItems[i].getID();
    }
}

void InventarioInterfaz::cargarVectorIDs(int vectorIDs[30])
{
    for (int i = 0; i < 30; i++)
    {
        _inventarioItems[i].setID(vectorIDs[i]);
    }
}

void InventarioInterfaz::copiarVectorDeCantidades(int vectorAlmacen[30])
{
    for (int i = 0; i < 30; i++)
    {
        vectorAlmacen[i] = _inventarioItems[i].getCantidad();
    }
}

void InventarioInterfaz::cargarVectorCantidades(int vectorCantidades[30])
{
    for (int i = 0; i < 30; i++)
    {
        _inventarioItems[i].setCantidad(vectorCantidades[i]);
    }
}

bool InventarioInterfaz::agregarItem(int ID, int cantidad)
{
    ///RECORRIDO PARA BUSCAR ID
    for(int i = 0; i < 30; i++)
    {
        if (_inventarioItems[i].getID() == ID)
        {
            int sumaCantidades = _inventarioItems[i].getCantidad() + cantidad;
            if (sumaCantidades > _inventarioItems[i].getCantidadMax())
            {
                _inventarioItems[i].setCantidad(_inventarioItems[i].getCantidadMax());
                cantidad = sumaCantidades - _inventarioItems[i].getCantidadMax();
            }
            else
            {
                _inventarioItems[i].setCantidad(sumaCantidades);
                return true;
            }
        }
    }
    ///RECORRIDO PARA BUSCAR 0
    if (cantidad != 0)
    {
        for(int i = 0; i < 30; i++)
        {
            if (_inventarioItems[i].getID() == -1)
            {
                _inventarioItems[i].setID(ID);
                if (cantidad > _inventarioItems[i].getCantidadMax())
                {
                    _inventarioItems[i].setCantidad(_inventarioItems[i].getCantidadMax());
                    cantidad -=  _inventarioItems[i].getCantidadMax();
                }
                else
                {
                    _inventarioItems[i].setCantidad(cantidad);
                    return true;
                }
            }
        }
    }
    return false;
}

bool InventarioInterfaz::quitarItem(int ID, int cantidad)
{
    int itemEncontrado = buscarItems(ID,cantidad);
    if (itemEncontrado != -1)   ///Si se encontro el item
    {
        _inventarioItems[itemEncontrado].setCantidad(_inventarioItems[itemEncontrado].getCantidad() - cantidad);
        return true;
    }
    return false;
}

int InventarioInterfaz::buscarItems(int ID, int cantidad)
{
    int cantidadEncontrados = 0;
    for(int i = 0; i < 30; i++)
    {
        if (_inventarioItems[i].getID() == ID)
        {
            cantidadEncontrados += _inventarioItems[i].getCantidad();
        }
        if (cantidadEncontrados >= cantidad) return i;
    }
    return -1;
}

void InventarioInterfaz::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();    // <---el estado sera el transformable del InventarioInterfaz

    target.draw(_sprFondoInventario,states);
    for(int i = 0; i < 30; i++)
    {
        if (_inventarioItems[i].getID() != -1) target.draw( _inventarioItems[i],states);
    }
    if (_hayItemEnMano)
    {
        target.draw(_itemEnMano);
    }
    ///Afectamos la escala del state para achicar la escala de descripcion
    states.transform.scale(0.5,0.5);
    target.draw(_descripcion,states);
}

bool InventarioInterfaz::sumarItems(Item& ItemIncrementador, Item& ItemIncrementado)
{
    int sumaCantidades = ItemIncrementado.getCantidad()+ItemIncrementador.getCantidad();
    if (sumaCantidades > ItemIncrementado.getCantidadMax())
    {
        int nuevaCantidad = sumaCantidades - ItemIncrementado.getCantidadMax();
        ItemIncrementado.setCantidad(ItemIncrementado.getCantidadMax());
        ItemIncrementador.setCantidad(nuevaCantidad);
        return false;
    }
    else
    {
        ItemIncrementado.setCantidad(sumaCantidades);
        ItemIncrementador.setID(-1);
        return true;
    }
}

void InventarioInterfaz::controlDeEventos(sf::Event& evento)
{
    if (evento.type == sf::Event::KeyPressed)
    {
        if (evento.key.code == sf::Keyboard::E && _botonAbrirInventarioDisponible)
        {
            _botonAbrirInventarioDisponible = false;
            setAbierto(!getAbierto());
        }
    }
    if (evento.type == sf::Event::KeyReleased){
            if (evento.key.code == sf::Keyboard::E) _botonAbrirInventarioDisponible = true;
    }
}

///Metodos privados
void InventarioInterfaz::ajustarEscalaAutomaticamente(const sf::View& vista, const float& relacionAspecto){
    ///Calculamos la escala X y Y
    setScale(sf::Vector2f( vista.getSize().x/512,  vista.getSize().y/512* relacionAspecto));

    float centroX = (_sprFondoInventario.getGlobalBounds().width/ 2) * getScale().x;

    setPosicionAbierto(vista.getCenter().x-centroX, vista.getCenter().y-vista.getSize().y/4);
    setPosicionEscondite(vista.getCenter().x-centroX, vista.getCenter().y+vista.getSize().y);

    if (!_primerVuelta){
        _primerVuelta = true;
        _posX = getPosicionEscondite().x;
        _posY = getPosicionEscondite().y;
    }

    if (!_abierto)
    {
        lerp(_posX, getPosicionEscondite().x, 0.1);
        lerp(_posY, getPosicionEscondite().y, 0.1);
        setPosition(_posX,_posY);
    }
    else
    {
        lerp(_posX, getPosicionAbierto().x, 0.1);
        lerp(_posY, getPosicionAbierto().y, 0.1);
        setPosition(_posX,_posY);
    }
}

void InventarioInterfaz::soltarLoot(Item& itemQueTirar, std::list<Loot>& listaLoots, bool tirarCompleto){
    sf::Vector2f posicionLoot;

    if (itemQueTirar.getID() != -1){
         if (tirarCompleto){
            int distanciaLoots = 4;
            const float PI = 3.1415926535f;
            for (int i = 0; i < itemQueTirar.getCantidad(); i++){

                posicionLoot = getPosicionAbierto();

                posicionLoot.x += (_sprFondoInventario.getGlobalBounds().width / 2) * getScale().x;
                posicionLoot.y += (_sprFondoInventario.getGlobalBounds().height+48) * getScale().y;

                float anguloGrados = (360.0f / itemQueTirar.getCantidad()) * i;
                float anguloRadianes = anguloGrados * (PI / 180.0f);

                posicionLoot.x += (cos(anguloRadianes)* distanciaLoots);
                posicionLoot.y += (sin(anguloRadianes)* distanciaLoots);
                listaLoots.emplace_back(*_texturaItems, posicionLoot, itemQueTirar.getID());
            }
            itemQueTirar.setID(-1);
        }
        else{
            posicionLoot = getPosicionAbierto();

            posicionLoot.x += (_sprFondoInventario.getGlobalBounds().width / 2) * getScale().x;
            posicionLoot.y += (_sprFondoInventario.getGlobalBounds().height+48) * getScale().y;

            listaLoots.emplace_back(*_texturaItems, posicionLoot, itemQueTirar.getID());
            int cantidadItem = itemQueTirar.getCantidad();
            if (cantidadItem > 1) itemQueTirar.setCantidad(cantidadItem - 1);
            else{
                itemQueTirar.setID(-1);
            }
        }
    }
}
