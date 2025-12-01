#include "InventarioIntefaz.h"
#include "funcionesInterpolacion.h"
#include <cmath>
#include <iostream>
#include <algorithm>
#include "InventarioResumidoInterfaz.h"
using namespace std;

/// CONSTRUCTOR - Inicializa el inventario con textura y fabrica de items
InventarioInterfaz::InventarioInterfaz(FabricaItems& fabItems, std::string nombreDireccionTextura)
{
    // Carga la textura del fondo del inventario
    _texturaFondo.loadFromFile(nombreDireccionTextura);
    _sprFondoInventario.setTexture(_texturaFondo);
    _sprFondoInventario.setOrigin(sf::Vector2f(0,0)); // Establece el origen en esquina superior izquierda

    // Almacena referencia a la fabrica de items para crear nuevos items
    _fabItems = &fabItems;

    // Inicializa todos los slots del inventario como vacios (nullptr)
    _itemEnMano = nullptr;
    _ptrItemEnManoActual = &_itemEnMano;
    for(int i = 0; i < 30; i++)
    {
        _inventarioItems[i] = nullptr;
    }
    cout << "creacion de inventario" << endl;
}

/// Mï¿½TODOS AUXILIARES PRIVADOS

// Crea una copia exacta de un item usando el patron prototype
std::unique_ptr<Item> InventarioInterfaz::clonarItem(const Item* item) const
{
    if (item == nullptr)
    {
        return nullptr;
    }
    auto clon = _fabItems->crearItem(item->getID());
    clon -> setCantidad(item->getCantidad());
    return clon;
}

// Intenta sumar las cantidades de dos items del mismo tipo
bool InventarioInterfaz::sumarItems(std::unique_ptr<Item>& ItemIncrementador, std::unique_ptr<Item>& ItemIncrementado)
{
    if (!ItemIncrementador || !ItemIncrementado) return false; // Verifica que ambos existan

    // Calcula la suma de cantidades
    int sumaCantidades = ItemIncrementado->getCantidad() + ItemIncrementador->getCantidad();

    // Si excede la cantidad maxima, divide los items
    if (sumaCantidades > ItemIncrementado->getCantidadMax())
    {
        int nuevaCantidad = sumaCantidades - ItemIncrementado->getCantidadMax();
        ItemIncrementado->setCantidad(ItemIncrementado->getCantidadMax()); // Llena al maximo
        ItemIncrementador->setCantidad(nuevaCantidad); // El sobrante queda en el otro item
        return false; // Indica que no se pudo sumar completamente
    }
    else
    {
        // Si cabe todo, suma y elimina el item sobrante
        ItemIncrementado->setCantidad(sumaCantidades);
        ItemIncrementador = nullptr;
        return true; // Indica ï¿½xito en la suma
    }
}

/// GETTERS - Metodos para obtener valores privados
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


void InventarioInterfaz::copiarItemsEnVector(Item* vectorDestino[30])
{
    for (int i = 0; i < 30; i++)
    {
        // Usamos .get() para obtener el puntero crudo del unique_ptr
        if (_inventarioItems[i] != nullptr)
        {
            vectorDestino[i] = _inventarioItems[i].get();
        }
        else
        {
            vectorDestino[i] = nullptr; // Aseguramos que sea nulo si no hay item
        }
    }
}


/// SETTERS - Metodos para modificar valores privados
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

/// METODO UPDATE PRINCIPAL - Actualiza logica e interacciones del inventario
void InventarioInterfaz::update(const sf::Vector2f& posGlobalDelMouse, const sf::View& vista, const float& relacionAspecto, std::list<Loot>& listaLoots)
{


    Comandos& input = Comandos::getInstancia();

    if (input.teclaInventarioRecienPresionada)
    {
        setAbierto(!getAbierto());
    }

    ajustarEscalaAutomaticamente(vista, relacionAspecto);


    bool mouseInteractuo = false; // Indica si el mouse interactua con algun slot

    // Procesa cada slot del inventario (30 slots total)
    for(int i = 0; i < 30; i++)
    {
        // Calcula posicion del slot en la grilla (10 columnas x 3 filas)
        int cantidadColumnas = 10;
        int columna = i % cantidadColumnas;
        int fila = i / cantidadColumnas;

        // Define area clickeable del slot
        _areasSeleccion[i].set_dimenciones(getPosition().x+columna*32*getScale().x,
                                           getPosition().x+(columna+1)*32*getScale().x,
                                           getPosition().y+fila*32*getScale().y,
                                           getPosition().y+(fila+1)*32*getScale().y);

        // Verifica si el mouse esta sobre este slot
        if (_areasSeleccion[i].estaDentro(posGlobalDelMouse.x, posGlobalDelMouse.y, true))
        {
            // Si hay item en el slot, muestra descripcion
            if(_inventarioItems[i] != nullptr)
            {
                mouseInteractuo = true;
                _descripcion.setVisible(true);
                _descripcion.setTitulo(_inventarioItems[i]->getTitulo());
                _descripcion.setDescripcion(_inventarioItems[i]->getDescripcion());

                // Posiciona la descripcion a izquierda o derecha segun columna
                if (i % 10 >= 5)
                {
                    _descripcion.EstablecerPosicion((posGlobalDelMouse.x-getPosition().x-(150 * getScale().x))/getScale().x*2,
                                                    (posGlobalDelMouse.y-getPosition().y)/getScale().y*2);
                }
                else
                {
                    _descripcion.EstablecerPosicion((posGlobalDelMouse.x-getPosition().x)/getScale().x*2,
                                                    (posGlobalDelMouse.y-getPosition().y)/getScale().y*2);
                }
                _descripcion.ActualizarDimensiones();
            }

            // Efecto visual: agranda item bajo el mouse
            if (_inventarioItems[i] != nullptr)
            {
                sf::Vector2f escalaActual(_inventarioItems[i]->getEscala());
                sf::Vector2f escalaObjetivo(1.25,1.25);
                lerp(escalaActual,escalaObjetivo,0.2); // Interpolacion suave
                _inventarioItems[i]->setEscala(escalaActual);
            }


            // Logica para boton Q (tirar item)

            if (input.teclaTirarRecienPresionada)
            {
                soltarLoot(_inventarioItems[i], listaLoots); // Suelta el item como loot
            }


            // Control de click derecho (dividir stacks)
            if (input.mouseDerRecienPresionado)
            {
                _indiceUltimoItemAnalizado = 100; // Reset
            }

            // Click derecho mantenido (transferir items uno por uno)
            if (input.mouseDerPresionado && i != _indiceUltimoItemAnalizado)
            {
                if((*_ptrItemEnManoActual) != nullptr)
                {
                    if (_inventarioItems[i] != nullptr)
                    {
                        // Si son del mismo tipo, transfiere uno
                        if (_inventarioItems[i]->getID() == (*_ptrItemEnManoActual)->getID())
                        {
                            if (_inventarioItems[i]->getCantidad() < _inventarioItems[i]->getCantidadMax())
                            {
                                if ((*_ptrItemEnManoActual)->getCantidad() > 1)
                                {
                                    (*_ptrItemEnManoActual)->setCantidad((*_ptrItemEnManoActual)->getCantidad() - 1);
                                    _inventarioItems[i]->setCantidad(_inventarioItems[i]->getCantidad() + 1);
                                    _indiceUltimoItemAnalizado = i;
                                }
                                else
                                {
                                    _inventarioItems[i]->setCantidad(_inventarioItems[i]->getCantidad() + 1);
                                    (*_ptrItemEnManoActual) = nullptr;
                                }
                            }
                        }
                    }
                    else
                    {
                        _indiceUltimoItemAnalizado = i;
                        if ((*_ptrItemEnManoActual) != nullptr)
                        {
                            if ((*_ptrItemEnManoActual)->getCantidad() > 1)
                            {
                                // Creamos clon de item con cantidad 1
                                auto nuevoItem = clonarItem((*_ptrItemEnManoActual).get());
                                nuevoItem->setCantidad(1);
                                _inventarioItems[i] = std::move(nuevoItem);
                                (*_ptrItemEnManoActual)->setCantidad((*_ptrItemEnManoActual)->getCantidad() - 1);
                            }
                            else
                            {
                                _inventarioItems[i] = std::move((*_ptrItemEnManoActual));
                            }
                        }
                    }
                }
            }

            // Click derecho
            if (input.mouseDerRecienPresionado)
            {

                // Si no hay item en mano, toma la mitad del stack
                if ((*_ptrItemEnManoActual) == nullptr)
                {
                    if (_inventarioItems[i] != nullptr)
                    {
                        if (_inventarioItems[i]->getCantidad() > 1)
                        {

                            (*_ptrItemEnManoActual) = clonarItem(_inventarioItems[i].get()); // Clona el item
                            // Divide la cantidad equitativamente
                            int division = _inventarioItems[i]->getCantidad() / 2;
                            int resto = _inventarioItems[i]->getCantidad() % 2;

                            if (resto != 0)
                            {
                                (*_ptrItemEnManoActual)->setCantidad(division);
                                _inventarioItems[i]->setCantidad(division + resto);
                            }
                            else
                            {
                                (*_ptrItemEnManoActual)->setCantidad(division);
                                _inventarioItems[i]->setCantidad(division);
                            }
                            _indiceUltimoItemAnalizado = i;
                        }
                    }
                }
                else
                {
                    // Si hay item en mano, intercambia o coloca
                    if (_inventarioItems[i] != nullptr)
                    {
                        if (_inventarioItems[i]->getID() != (*_ptrItemEnManoActual)->getID())
                        {
                            (*_ptrItemEnManoActual)->setEscala(sf::Vector2f(1.3,1.3));
                            std::swap(_inventarioItems[i], (*_ptrItemEnManoActual)); // Intercambia items
                        }
                    }
                    else
                    {
                        // Coloca item en slot vacio
                        _inventarioItems[i] = std::move((*_ptrItemEnManoActual));

                    }
                }
            }

            // Logica para click izquierdo (agarrar/soltar items)
            if (input.mouseIzqRecienPresionado)
            {
                if (_inventarioItems[i] != nullptr || (*_ptrItemEnManoActual) != nullptr)
                {

                    // Si no hay item en mano, agarra el del slot
                    if((*_ptrItemEnManoActual) == nullptr)
                    {
                        if(_inventarioItems[i] != nullptr)
                        {

                            (*_ptrItemEnManoActual) = std::move(_inventarioItems[i]); // Transfiere propiedad
                        }
                    }
                    else
                    {
                        // Si hay item en mano, intenta combinarlo o intercambiarlo
                        if (_inventarioItems[i] != nullptr)
                        {
                            if (_inventarioItems[i]->getID() == (*_ptrItemEnManoActual)->getID())
                            {
                                // Son del mismo tipo - intenta sumar
                                sumarItems((*_ptrItemEnManoActual), _inventarioItems[i]);
                            }
                            else
                            {
                                // Son diferentes - intercambia
                                std::swap((*_ptrItemEnManoActual), _inventarioItems[i]);
                            }
                        }
                        else
                        {   // Slot vacio - coloca item
                            _inventarioItems[i] = std::move((*_ptrItemEnManoActual));
                        }
                    }


                    // Logica de doble click (auto-organizacion)
                    if (input.mouseIzqDobleClick)
                    {
                        if((*_ptrItemEnManoActual) != nullptr)
                        {
                            if ((*_ptrItemEnManoActual)->getCantidad() < (*_ptrItemEnManoActual)->getCantidadMax())
                            {
                                // Busca todos los slots con items del mismo tipo
                                std::vector<int> indices_slots_con_item;

                                for (int x = 0; x < 30; x++)
                                {
                                    if (_inventarioItems[x] != nullptr)
                                    {
                                        if (_inventarioItems[x]->getID() == (*_ptrItemEnManoActual)->getID())
                                        {
                                            indices_slots_con_item.push_back(x);
                                            if ((*_ptrItemEnManoActual)->getCantidad() == (*_ptrItemEnManoActual)->getCantidadMax()) break;
                                        }
                                    }
                                }

                                // Combina con otros stacks del mismo tipo
                                while ((*_ptrItemEnManoActual)->getCantidad() < (*_ptrItemEnManoActual)->getCantidadMax() && !indices_slots_con_item.empty())
                                {
                                    int indice_mas_chico = -1;
                                    int cantidad_minima = -1;
                                    int indice_en_vector = -1;

                                    // Encuentra el stack mas pequenio
                                    for (size_t uwu = 0; uwu < indices_slots_con_item.size(); ++uwu)
                                    {
                                        int indice_actual = indices_slots_con_item[uwu];
                                        if (_inventarioItems[indice_actual] == nullptr) continue;
                                        int cantidad_actual = _inventarioItems[indice_actual]->getCantidad();

                                        if (cantidad_actual > 0 && (cantidad_minima == -1 || cantidad_actual < cantidad_minima))
                                        {
                                            cantidad_minima = cantidad_actual;
                                            indice_mas_chico = indice_actual;
                                            indice_en_vector = uwu;
                                        }
                                    }

                                    if (indice_mas_chico == -1) break;

                                    // Suma los items
                                    sumarItems(_inventarioItems[indice_mas_chico], (*_ptrItemEnManoActual));
                                    if (_inventarioItems[indice_mas_chico] == nullptr)
                                    {
                                        if (indice_en_vector >= 0 && indice_en_vector < (int)indices_slots_con_item.size())
                                            indices_slots_con_item.erase(indices_slots_con_item.begin() + indice_en_vector);
                                    }
                                }
                            }
                        }
                    }

                }
            }
        }
        else
        {
            // Mouse NO esta sobre este slot - restaura escala normal
            if (_inventarioItems[i] != nullptr)
            {
                sf::Vector2f escalaActual(_inventarioItems[i]->getEscala());
                sf::Vector2f escalaObjetivo(1,1);
                lerp(escalaActual,escalaObjetivo,0.2); // Interpolacion suave a escala normal
                _inventarioItems[i]->setEscala(escalaActual);
            }
        }
        if (_inventarioItems[i] != nullptr)
        {
            _inventarioItems[i]->setPosition(16 + columna * 32, 16 + fila * 32); // Posicion en grid
            _inventarioItems[i]->actualizarSprite();
        }
    }


    // Maneja el item que esta siendo arrastrado con el mouse
    if ((*_ptrItemEnManoActual) != nullptr)
    {
        if ((*_ptrItemEnManoActual) != nullptr)
        {
            (*_ptrItemEnManoActual)->setPosition(posGlobalDelMouse.x, posGlobalDelMouse.y); // Sigue al mouse
            (*_ptrItemEnManoActual)->setEscala(sf::Vector2f(1.3 * getScale().x, 1.3 * getScale().y));
            (*_ptrItemEnManoActual)->actualizarSprite();
        }
        // Si clickea fuera del inventario, suelta el item como loot
        if (!mouseInteractuo)
        {
            if (input.mouseIzqRecienPresionado)
            {

                soltarLoot((*_ptrItemEnManoActual), listaLoots, true); // Tirar todo el stack
            }
        }
    }

    // Oculta descripcion si no hay interaccion o hay item en mano
    if(!mouseInteractuo || (*_ptrItemEnManoActual) != nullptr)
    {
        _descripcion.setVisible(false);
    }





}

/// METODOS DE PERSISTENCIA - Para guardar/cargar el inventario

// Copia los IDs de los items a un array para guardar
void InventarioInterfaz::copiarVectorDeIDs(int vectorAlmacen[30])
{
    for (int i = 0; i < 30; i++)
    {
        if (_inventarioItems[i] != nullptr)
            vectorAlmacen[i] = _inventarioItems[i]->getID(); // ID del item
        else
            vectorAlmacen[i] = -1; // -1 indica slot vacio
    }
}

// Carga items desde un array de IDs
void InventarioInterfaz::cargarVectorIDs(int vectorIDs[30])
{
    for (int i = 0; i < 30; i++)
    {
        if (vectorIDs[i] != -1)
            _inventarioItems[i] = _fabItems->crearItem(vectorIDs[i]); // Crea nuevo item
        else
            _inventarioItems[i] = nullptr; // Slot vacio
    }
}

// Copia las cantidades de los items para guardar
void InventarioInterfaz::copiarVectorDeCantidades(int vectorAlmacen[30])
{
    for (int i = 0; i < 30; i++)
    {
        if (_inventarioItems[i] != nullptr)
            vectorAlmacen[i] = _inventarioItems[i]->getCantidad(); // Cantidad actual
        else
            vectorAlmacen[i] = 0; // 0 indica slot vacio
    }
}

// Carga cantidades desde un array
void InventarioInterfaz::cargarVectorCantidades(int vectorCantidades[30])
{
    for (int i = 0; i < 30; i++)
    {
        if (_inventarioItems[i] != nullptr)
            _inventarioItems[i]->setCantidad(vectorCantidades[i]); // Restaura cantidad
    }
}

/// Mï¿½TODOS DE GESTION DE ITEMS

// Agrega un item al inventario (busca slots existentes primero, luego vacios)
bool InventarioInterfaz::agregarItem(int ID, int cantidad)
{
    // Primero intenta agregar a stacks existentes del mismo tipo
    for(int i = 0; i < 30 && cantidad > 0; i++)
    {
        if (_inventarioItems[i] != nullptr && _inventarioItems[i]->getID() == ID)
        {
            int espacioDisponible = _inventarioItems[i]->getCantidadMax() - _inventarioItems[i]->getCantidad();
            int aAgregar = std::min(cantidad, espacioDisponible); // No exceder maximo

            if (aAgregar > 0)
            {
                _inventarioItems[i]->setCantidad(_inventarioItems[i]->getCantidad() + aAgregar);
                cantidad -= aAgregar; // Reduce cantidad pendiente
            }
        }
    }

    // Luego usa slots vacios para lo que queda
    for(int i = 0; i < 30 && cantidad > 0; i++)
    {
        if (_inventarioItems[i] == nullptr)
        {
            _inventarioItems[i] = _fabItems->crearItem(ID); // Crea nuevo item
            if (_inventarioItems[i] != nullptr)
            {
                int aAgregar = std::min(cantidad, _inventarioItems[i]->getCantidadMax());
                _inventarioItems[i]->setCantidad(aAgregar);
                cantidad -= aAgregar;
            }
        }
    }

    return cantidad == 0; // True si se pudo agregar todo, False si sobro
}

// Quita una cantidad especifica de un tipo de item
bool InventarioInterfaz::quitarItem(int ID, int cantidad)
{
    if (buscarItems(ID, cantidad) == -1)
    {
        return false;
    }

    for(int i = 0; i < 30 && cantidad > 0; i++)
    {
        // Si el slot tiene el ¡tem que buscamos
        if (_inventarioItems[i] != nullptr && _inventarioItems[i]->getID() == ID)
        {
            int cantidadEnEsteSlot = _inventarioItems[i]->getCantidad();

            if (cantidadEnEsteSlot > cantidad)
            {
                // CASO A: El slot tiene de sobra.
                // Le restamos lo que falta y terminamos.
                _inventarioItems[i]->setCantidad(cantidadEnEsteSlot - cantidad);
                cantidad = 0; // Deuda saldada
            }
            else
            {
                // CASO B: El slot tiene justo o menos de lo que necesitamos.
                // Lo vaciamos entero y seguimos buscando en el siguiente slot.
                cantidad -= cantidadEnEsteSlot; // Restamos lo que pudimos sacar de ac 

                _inventarioItems[i] = nullptr; // ELIMINAMOS EL OBJETO (Slot vac¡o)
            }
        }
    }

    return true; // Operaci¢n exitosa
}

// Busca si hay suficiente cantidad de un tipo de item
int InventarioInterfaz::buscarItems(int ID, int cantidad)
{
    int cantidadEncontrados = 0;
    for(int i = 0; i < 30; i++)
    {
        if (_inventarioItems[i] != nullptr)
        {
            if (_inventarioItems[i]->getID() == ID)
            {
                cantidadEncontrados += _inventarioItems[i]->getCantidad();
            }
            if (cantidadEncontrados >= cantidad) return i; // Devuelve ï¿½ndice cuando encuentra suficiente
        }
    }
    return -1; // No se encontro suficiente cantidad
}

/// METODO DE DIBUJO - Renderiza el inventario y sus items
void InventarioInterfaz::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform(); // Aplica transformaciones del inventario

    target.draw(_sprFondoInventario, states); // Dibuja fondo

    // Dibuja todos los items del inventario
    for(int i = 0; i < 30; i++)
    {
        if (_inventarioItems[i] != nullptr)
            target.draw(*_inventarioItems[i], states);
    }

    /*
    // Dibuja el item que esta siendo arrastrado (si existe)
    if ((*_ptrItemEnManoActual) != nullptr)
    {
        target.draw(*(*_ptrItemEnManoActual));
    }*/

    if (!const_cast<InventarioInterfaz*>(this)->usaItemEnManoExterno())
    {
        if (*_ptrItemEnManoActual != nullptr)
        {
            target.draw(**_ptrItemEnManoActual);
        }
    }

    // Dibuja la descripcion (con escala reducida)
    states.transform.scale(0.5, 0.5);
    target.draw(_descripcion, states);
}


/// METODOS AUXILIARES PRIVADOS (continuacion)

// Ajusta escala y posicion del inventario segun la vista de camara
void InventarioInterfaz::ajustarEscalaAutomaticamente(const sf::View& vista, const float& relacionAspecto)
{
    // Escala proporcional al tamanio de la vista
    setScale(sf::Vector2f(vista.getSize().x/512, vista.getSize().y/512 * relacionAspecto));

    float centroX = (_sprFondoInventario.getGlobalBounds().width/ 2) * getScale().x;

    // Calcula posiciones para estado abierto y cerrado
    setPosicionAbierto(vista.getCenter().x - centroX, vista.getCenter().y - vista.getSize().y/4);
    setPosicionEscondite(vista.getCenter().x - centroX, vista.getCenter().y + vista.getSize().y);

    // Inicializacion en primera ejecucion
    if (!_primerVuelta)
    {
        _primerVuelta = true;
        _posX = getPosicionEscondite().x;
        _posY = getPosicionEscondite().y;
    }

    // Animacion suave de apertura/cierre
    if (!_abierto)
    {
        lerp(_posX, getPosicionEscondite().x, 0.1); // Interpolacion a posicion escondida
        lerp(_posY, getPosicionEscondite().y, 0.1);
        setPosition(_posX, _posY);
    }
    else
    {
        lerp(_posX, getPosicionAbierto().x, 0.1); // Interpolacion a posicion visible
        lerp(_posY, getPosicionAbierto().y, 0.1);
        setPosition(_posX, _posY);
    }
}

// Suelta un item del inventario como loot en el mundo
void InventarioInterfaz::soltarLoot(std::unique_ptr<Item>& itemQueTirar, std::list<Loot>& listaLoots, bool tirarCompleto)
{
    sf::Vector2f posicionLoot;

    if (itemQueTirar != nullptr)
    {
        if (tirarCompleto)
        {
            // Tirar todo el stack - crea loots individuales en cï¿½rculo
            int distanciaLoots = 4;
            const float PI = 3.1415926535f;
            for (int i = 0; i < itemQueTirar->getCantidad(); i++)
            {
                posicionLoot = getPosicionAbierto();
                posicionLoot.x += (_sprFondoInventario.getGlobalBounds().width / 2) * getScale().x;
                posicionLoot.y += (_sprFondoInventario.getGlobalBounds().height + 48) * getScale().y;

                // Distribuye en cï¿½rculo
                float anguloGrados = (360.0f / itemQueTirar->getCantidad()) * i;
                float anguloRadianes = anguloGrados * (PI / 180.0f);

                posicionLoot.x += (cos(anguloRadianes) * distanciaLoots);
                posicionLoot.y += (sin(anguloRadianes) * distanciaLoots);
                listaLoots.emplace_back(*_fabItems, posicionLoot, itemQueTirar->getID());
            }
            itemQueTirar = nullptr; // Elimina el item del inventario
        }
        else
        {
            // Tirar solo un item del stack
            posicionLoot = getPosicionAbierto();
            posicionLoot.x += (_sprFondoInventario.getGlobalBounds().width / 2) * getScale().x;
            posicionLoot.y += (_sprFondoInventario.getGlobalBounds().height + 48) * getScale().y;

            listaLoots.emplace_back(*_fabItems, posicionLoot, itemQueTirar->getID());
            int cantidadItem = itemQueTirar->getCantidad();
            if (cantidadItem > 1)
                itemQueTirar->setCantidad(cantidadItem - 1); // Reduce cantidad
            else
                itemQueTirar = nullptr; // Elimina si era el ultimo
        }
    }
}

void InventarioInterfaz::setInventarioResumido(InventarioResumido* InvR) {
    _inventarioResumido = InvR;
}

InventarioResumido* InventarioInterfaz::getInventarioResumido() {
    return _inventarioResumido;
}

void InventarioInterfaz::consumirItemEnSlot(int slot, int cantidad)
{
    if (slot >= 0 && slot < 30)
    {
        if (_inventarioItems[slot] != nullptr)
        {
            int nuevaCantidad = _inventarioItems[slot]->getCantidad() - cantidad;

            if (nuevaCantidad <= 0)
            {
                _inventarioItems[slot] = nullptr;
            }
            else
            {
                _inventarioItems[slot]->setCantidad(nuevaCantidad);
            }
        }
    }
}

Item* InventarioInterfaz::getItemEnMano()
{
    if (_inventarioResumido != nullptr)
    {
        return _inventarioResumido->getItem(_inventarioResumido->getSlotSeleccionado());
    }
    return nullptr;
}

std::unique_ptr<Item>* InventarioInterfaz::obtenerPunteroItemEnMano()
{
    // Devolvemos la direcci¢n de memoria de nuestra variable local
    return &(*_ptrItemEnManoActual);
}

void InventarioInterfaz::enlazarItemEnMano(std::unique_ptr<Item>* punteroExterno)
{
    if (punteroExterno != nullptr)
    {
        _ptrItemEnManoActual = punteroExterno;
    }
    else
    {
        // Si nos pasan nullptr, volvemos a usar el nuestro propio
        _ptrItemEnManoActual = &_itemEnMano;
    }
}

bool InventarioInterfaz::usaItemEnManoExterno()
{
    return _ptrItemEnManoActual != &_itemEnMano;
}
