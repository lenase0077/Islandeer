#include "InventarioIntefaz.h"
#include "funcionesInterpolacion.h"
#include <cmath>
#include <iostream>
#include <algorithm>

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
    for(int i = 0; i < 30; i++)
    {
        _inventarioItems[i] = nullptr;
    }
    cout << "creacion de inventario" << endl;
}

/// MÉTODOS AUXILIARES PRIVADOS

// Crea una copia exacta de un item usando el patrón prototype
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

// Verifica si dos items son del mismo tipo comparando sus IDs
bool InventarioInterfaz::sonMismoTipo(const Item* a, const Item* b) const
{
    if (!a || !b) return false; // Si alguno es nulo, no son del mismo tipo
    return a->getID() == b->getID(); // Compara IDs
}

// Intenta sumar las cantidades de dos items del mismo tipo
bool InventarioInterfaz::sumarItems(std::unique_ptr<Item>& ItemIncrementador, std::unique_ptr<Item>& ItemIncrementado)
{
    if (!ItemIncrementador || !ItemIncrementado) return false; // Verifica que ambos existan

    // Calcula la suma de cantidades
    int sumaCantidades = ItemIncrementado->getCantidad() + ItemIncrementador->getCantidad();

    // Si excede la cantidad máxima, divide los items
    if (sumaCantidades > ItemIncrementado->getCantidadMax())
    {
        int nuevaCantidad = sumaCantidades - ItemIncrementado->getCantidadMax();
        ItemIncrementado->setCantidad(ItemIncrementado->getCantidadMax()); // Llena al máximo
        ItemIncrementador->setCantidad(nuevaCantidad); // El sobrante queda en el otro item
        return false; // Indica que no se pudo sumar completamente
    }
    else
    {
        // Si cabe todo, suma y elimina el item sobrante
        ItemIncrementado->setCantidad(sumaCantidades);
        ItemIncrementador = nullptr;
        return true; // Indica éxito en la suma
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
void InventarioInterfaz::update(const sf::Vector2f& posGlobalDelMouse, const sf::Mouse& mouse,
                                const sf::View& vista, const float& relacionAspecto,
                                std::list<Loot>& listaLoots, sf::Keyboard& tecladoEntrada)
{
    ajustarEscalaAutomaticamente(vista, relacionAspecto);

    bool izquierdoPresionadoActual = mouse.isButtonPressed(sf::Mouse::Left);
    bool izquierdoRecienPresionado = izquierdoPresionadoActual && !_izquierdoPresionadoAnterior;

    // Control de doble click - resetea contador despues de 250ms
    if (_timerDobleClick2.getElapsedTime().asMilliseconds() >= 250)
    {
        _contadorClicksIzquierdo = 0;
    }

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
            // Si hay item en el slot, muestra descripción
            if(_inventarioItems[i] != nullptr)
            {
                mouseInteractuo = true;
                _descripcion.setVisible(true);
                _descripcion.setTitulo(_inventarioItems[i]->getTitulo());
                _descripcion.setDescripcion(_inventarioItems[i]->getDescripcion());

                // Posiciona la descripción a izquierda o derecha según columna
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
                lerp(escalaActual,escalaObjetivo,0.2); // Interpolación suave
                _inventarioItems[i]->setEscala(escalaActual);
            }


            // Lógica para botón Q (tirar item)
            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            {
                _frameActualQprecionada = false;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && !_frameActualQprecionada)
            {
                _frameActualQprecionada = true;
                soltarLoot(_inventarioItems[i], listaLoots); // Suelta el item como loot
            }


            // Control de click derecho (dividir stacks)
            if (!_clickDerechoDisponible && (!mouse.isButtonPressed(sf::Mouse::Right)))
            {
                _clickDerechoDisponible = true;
                _indiceUltimoItemAnalizado = 100; // Reset
            }




            ///FUNCIONA PERFECTAMENTE=====================================================

            ///=============


            // Click derecho mantenido (transferir items uno por uno)
            if (mouse.isButtonPressed(sf::Mouse::Right) && i != _indiceUltimoItemAnalizado)
            {
                if(_itemEnMano != nullptr)
                {
                    if (_inventarioItems[i] != nullptr)
                    {
                        // Si son del mismo tipo, transfiere uno
                        if (_inventarioItems[i]->getID() == _itemEnMano->getID())
                        {
                            if (_inventarioItems[i]->getCantidad() < _inventarioItems[i]->getCantidadMax())
                            {
                                if (_itemEnMano->getCantidad() > 1)
                                {
                                    _itemEnMano->setCantidad(_itemEnMano->getCantidad() - 1);
                                    _inventarioItems[i]->setCantidad(_inventarioItems[i]->getCantidad() + 1);
                                    _indiceUltimoItemAnalizado = i;
                                }
                                else
                                {
                                    _inventarioItems[i]->setCantidad(_inventarioItems[i]->getCantidad() + 1);
                                    _itemEnMano = nullptr;
                                }
                            }
                        }
                    }
                    else
                    {
                        _indiceUltimoItemAnalizado = i;
                        if (_itemEnMano != nullptr)
                        {
                            if (_itemEnMano->getCantidad() > 1)
                            {
                                // Creamos clon de item con cantidad 1
                                auto nuevoItem = clonarItem(_itemEnMano.get());
                                nuevoItem->setCantidad(1);
                                _inventarioItems[i] = std::move(nuevoItem);
                                _itemEnMano->setCantidad(_itemEnMano->getCantidad() - 1);
                            }
                            else
                            {
                                _inventarioItems[i] = std::move(_itemEnMano);
                            }
                        }
                    }
                }
            }

            // Click derecho
            if (mouse.isButtonPressed(sf::Mouse::Right) && _clickDerechoDisponible)
            {
                _contadorClicksIzquierdo = 0;
                _timerDobleClick2.restart();
                _clickDerechoDisponible = false;

                // Si no hay item en mano, toma la mitad del stack
                if (_itemEnMano == nullptr)
                {
                    if (_inventarioItems[i] != nullptr)
                    {
                        if (_inventarioItems[i]->getCantidad() > 1)
                        {

                            _itemEnMano = clonarItem(_inventarioItems[i].get()); // Clona el item
                            // Divide la cantidad equitativamente
                            int division = _inventarioItems[i]->getCantidad() / 2;
                            int resto = _inventarioItems[i]->getCantidad() % 2;

                            if (resto != 0)
                            {
                                _itemEnMano->setCantidad(division);
                                _inventarioItems[i]->setCantidad(division + resto);
                            }
                            else
                            {
                                _itemEnMano->setCantidad(division);
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
                        if (_inventarioItems[i]->getID() != _itemEnMano->getID())
                        {
                            _itemEnMano->setEscala(sf::Vector2f(1.3,1.3));
                            std::swap(_inventarioItems[i], _itemEnMano); // Intercambia items
                        }
                    }
                    else
                    {
                        // Coloca item en slot vacio
                        _inventarioItems[i] = std::move(_itemEnMano);

                    }
                }
            }


            //=============================

            // Lógica para click izquierdo (agarrar/soltar items)
            if (izquierdoRecienPresionado)
            {
                if (_inventarioItems[i] != nullptr || _itemEnMano != nullptr)
                {
                    _timerDobleClick2.restart();
                    _contadorClicksIzquierdo++;

                    // Si no hay item en mano, agarra el del slot
                    if(_itemEnMano == nullptr)
                    {
                        if(_inventarioItems[i] != nullptr)
                        {

                            _itemEnMano = std::move(_inventarioItems[i]); // Transfiere propiedad
                        }
                    }
                    else
                    {
                        // Si hay item en mano, intenta combinarlo o intercambiarlo
                        if (_inventarioItems[i] != nullptr)
                        {
                            if (_inventarioItems[i]->getID() == _itemEnMano->getID())
                            {
                                // Son del mismo tipo - intenta sumar
                                sumarItems(_itemEnMano, _inventarioItems[i]);
                            }
                            else
                            {
                                // Son diferentes - intercambia
                                std::swap(_itemEnMano, _inventarioItems[i]);
                            }
                        }
                        else
                        {
                            // Slot vacio - coloca item

                            _inventarioItems[i] = std::move(_itemEnMano);
                        }
                    }


                    // Lógica de doble click (auto-organización)
                    if (_contadorClicksIzquierdo >= 2)
                    {
                        if(_itemEnMano != nullptr)
                        {
                            if (_itemEnMano->getCantidad() < _itemEnMano->getCantidadMax())
                            {
                                // Busca todos los slots con items del mismo tipo
                                std::vector<int> indices_slots_con_item;

                                for (int x = 0; x < 30; x++)
                                {
                                    if (_inventarioItems[x] != nullptr)
                                    {
                                        if (_inventarioItems[x]->getID() == _itemEnMano->getID())
                                        {
                                            indices_slots_con_item.push_back(x);
                                            if (_itemEnMano->getCantidad() == _itemEnMano->getCantidadMax()) break;
                                        }
                                    }
                                }

                                // Combina con otros stacks del mismo tipo
                                while (_itemEnMano->getCantidad() < _itemEnMano->getCantidadMax() && !indices_slots_con_item.empty())
                                {
                                    int indice_mas_chico = -1;
                                    int cantidad_minima = -1;
                                    int indice_en_vector = -1;

                                    // Encuentra el stack más pequeño
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
                                    sumarItems(_inventarioItems[indice_mas_chico], _itemEnMano);
                                    if (_inventarioItems[indice_mas_chico] == nullptr)
                                    {
                                        if (indice_en_vector >= 0 && indice_en_vector < (int)indices_slots_con_item.size())
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
            // Mouse NO esta sobre este slot - restaura escala normal
            if (_inventarioItems[i] != nullptr)
            {
                sf::Vector2f escalaActual(_inventarioItems[i]->getEscala());
                sf::Vector2f escalaObjetivo(1,1);
                lerp(escalaActual,escalaObjetivo,0.2); // Interpolación suave a escala normal
                _inventarioItems[i]->setEscala(escalaActual);
            }
        }
        if (_inventarioItems[i] != nullptr)
        {
            _inventarioItems[i]->setPosition(16 + columna * 32, 16 + fila * 32); // Posicion en grid
            _inventarioItems[i]->actualizarSprite();
        }
    }


    _izquierdoPresionadoAnterior = izquierdoPresionadoActual; // Guarda estado para siguiente frame

    // Maneja el item que está siendo arrastrado con el mouse
    if (_itemEnMano != nullptr)
    {
        if (_itemEnMano != nullptr)
        {
            _itemEnMano->setPosition(posGlobalDelMouse.x, posGlobalDelMouse.y); // Sigue al mouse
            _itemEnMano->setEscala(sf::Vector2f(1.3 * getScale().x, 1.3 * getScale().y));
            _itemEnMano->actualizarSprite();
        }
        // Si clickea fuera del inventario, suelta el item como loot
        if (!mouseInteractuo)
        {
            if (izquierdoRecienPresionado)
            {

                soltarLoot(_itemEnMano, listaLoots, true); // Tirar todo el stack
            }
        }
    }

    // Oculta descripción si no hay interacción o hay item en mano
    if(!mouseInteractuo || _itemEnMano != nullptr)
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

/// MÉTODOS DE GESTION DE ITEMS

// Agrega un item al inventario (busca slots existentes primero, luego vacios)
bool InventarioInterfaz::agregarItem(int ID, int cantidad)
{
    // Primero intenta agregar a stacks existentes del mismo tipo
    for(int i = 0; i < 30 && cantidad > 0; i++)
    {
        if (_inventarioItems[i] != nullptr && _inventarioItems[i]->getID() == ID)
        {
            int espacioDisponible = _inventarioItems[i]->getCantidadMax() - _inventarioItems[i]->getCantidad();
            int aAgregar = std::min(cantidad, espacioDisponible); // No exceder máximo

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

    return cantidad == 0; // True si se pudo agregar todo, False si sobró
}

// Quita una cantidad especifica de un tipo de item
bool InventarioInterfaz::quitarItem(int ID, int cantidad)
{
    int itemEncontrado = buscarItems(ID, cantidad);
    if (itemEncontrado != -1)
    {
        if (_inventarioItems[itemEncontrado] != nullptr)
        {
            int nueva = _inventarioItems[itemEncontrado]->getCantidad() - cantidad;
            if (nueva > 0)
                _inventarioItems[itemEncontrado]->setCantidad(nueva); // Reduce cantidad
            else
                _inventarioItems[itemEncontrado] = nullptr; // Elimina si llega a 0
            return true;
        }
    }
    return false; // No se encontraron suficientes items
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
            if (cantidadEncontrados >= cantidad) return i; // Devuelve índice cuando encuentra suficiente
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

    // Dibuja el item que está siendo arrastrado (si existe)
    if (_itemEnMano != nullptr && _itemEnMano != nullptr)
    {
        target.draw(*_itemEnMano);
    }

    // Dibuja la descripción (con escala reducida)
    states.transform.scale(0.5, 0.5);
    target.draw(_descripcion, states);
}

/// CONTROL DE EVENTOS - Maneja entrada de teclado
void InventarioInterfaz::controlDeEventos(sf::Event& evento)
{
    if (evento.type == sf::Event::KeyPressed)
    {
        if (evento.key.code == sf::Keyboard::E && _botonAbrirInventarioDisponible)
        {
            _botonAbrirInventarioDisponible = false;
            setAbierto(!getAbierto()); // Abre/cierra inventario con tecla E
        }
    }
    if (evento.type == sf::Event::KeyReleased)
    {
        if (evento.key.code == sf::Keyboard::E) _botonAbrirInventarioDisponible = true; // Habilita nuevamente
    }
}

/// METODOS AUXILIARES PRIVADOS (continuación)

// Ajusta escala y posición del inventario según la vista de cámara
void InventarioInterfaz::ajustarEscalaAutomaticamente(const sf::View& vista, const float& relacionAspecto)
{
    // Escala proporcional al tamaño de la vista
    setScale(sf::Vector2f(vista.getSize().x/512, vista.getSize().y/512 * relacionAspecto));

    float centroX = (_sprFondoInventario.getGlobalBounds().width/ 2) * getScale().x;

    // Calcula posiciones para estado abierto y cerrado
    setPosicionAbierto(vista.getCenter().x - centroX, vista.getCenter().y - vista.getSize().y/4);
    setPosicionEscondite(vista.getCenter().x - centroX, vista.getCenter().y + vista.getSize().y);

    // Inicialización en primera ejecución
    if (!_primerVuelta)
    {
        _primerVuelta = true;
        _posX = getPosicionEscondite().x;
        _posY = getPosicionEscondite().y;
    }

    // Animacion suave de apertura/cierre
    if (!_abierto)
    {
        lerp(_posX, getPosicionEscondite().x, 0.1); // Interpolación a posición escondida
        lerp(_posY, getPosicionEscondite().y, 0.1);
        setPosition(_posX, _posY);
    }
    else
    {
        lerp(_posX, getPosicionAbierto().x, 0.1); // Interpolación a posición visible
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
            // Tirar todo el stack - crea loots individuales en círculo
            int distanciaLoots = 4;
            const float PI = 3.1415926535f;
            for (int i = 0; i < itemQueTirar->getCantidad(); i++)
            {
                posicionLoot = getPosicionAbierto();
                posicionLoot.x += (_sprFondoInventario.getGlobalBounds().width / 2) * getScale().x;
                posicionLoot.y += (_sprFondoInventario.getGlobalBounds().height + 48) * getScale().y;

                // Distribuye en círculo
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
                itemQueTirar = nullptr; // Elimina si era el último
        }
    }
}
