#include "InterfazBarcoHuida.h"
#include "Comando.h"
#include "funcionesInterpolacion.h"
#include <iostream>


using namespace std;

InterfazBarcoHuida::InterfazBarcoHuida(const sf::Texture& texturaFondoInterfaz, const sf::Texture& texturaBotonesDePagina, const sf::Font& fuente, FabricaItems& fabItems)
{
    _texturaFondoInterfaz = &texturaFondoInterfaz;
    _sprfondoInterfaz.setTexture(texturaFondoInterfaz);

    //botones de pagina
    _texturaBotonesDePagina = &texturaBotonesDePagina;
    _sprBotonPagAnterior.setTexture(texturaBotonesDePagina);
    _sprBotonPagSiguiente.setTexture(texturaBotonesDePagina);

    _sprBotonPagAnterior.setTextureRect({0,0,16,16});
    _sprBotonPagSiguiente.setTextureRect({16,0,16,16});

    //borde seleccion
    _bordeSeleccion.setFillColor(sf::Color::Transparent);
    _bordeSeleccion.setOutlineThickness(1);
    _bordeSeleccion.setOutlineColor(sf::Color::White);

    //Audio subrayado
    if (!_bufferSonidoLapiz.loadFromFile("SonidoLapiz.wav"))
    {
        cout << "no se pudo cargar el audio SonidoLapiz.wav" << endl;
    }
    _sonidoLapiz.setBuffer(_bufferSonidoLapiz);
    _sonidoLapiz.setVolume(2.0);
    _sonidoLapiz.setLoop(false);

    _titulos[0] = "Kit de Construccion Naval";
    _titulos[1] = "Suministros y Cocina";
    _titulos[2] = "Hidratacion y Almacenamiento";
    _titulos[3] = "Seguridad y Salud Mental";

    _paginaCompletada[0] = false;
    _paginaCompletada[1] = false;
    _paginaCompletada[2] = false;
    _paginaCompletada[3] = false;

    _textoTitulo.setFont(fuente);
    _textoTitulo.setColor(sf::Color::Black);
    _textoTitulo.setCharacterSize(8);

    ///Agregamos los requisitos
    //Primer pagina
    /*_ItemsRequeridos[0].push_back(fabItems.crearItem(52));//mesa de crafteo
    _cantidadNecesaria[0].push_back(1);
    _ItemsRequeridos[0].push_back(fabItems.crearItem(5));//Hacha de diamante
    _cantidadNecesaria[0].push_back(1);
    _ItemsRequeridos[0].push_back(fabItems.crearItem(10));//Palo x 100
    _cantidadNecesaria[0].push_back(100);
    _ItemsRequeridos[0].push_back(fabItems.crearItem(14));//Soga x 50
    _cantidadNecesaria[0].push_back(50);

    //Segunda Pagina
    _ItemsRequeridos[1].push_back(fabItems.crearItem(50));//Horno x 1
    _cantidadNecesaria[1].push_back(1);
    _ItemsRequeridos[1].push_back(fabItems.crearItem(19));//Carb¢n x 200
    _cantidadNecesaria[1].push_back(200);
    _ItemsRequeridos[1].push_back(fabItems.crearItem(48));//Carne Cocida x 50
    _cantidadNecesaria[1].push_back(50);
    _ItemsRequeridos[1].push_back(fabItems.crearItem(36));//Coco x 100
    _cantidadNecesaria[1].push_back(100);
    _ItemsRequeridos[1].push_back(fabItems.crearItem(41));//Papa Cocinada x 50
    _cantidadNecesaria[1].push_back(50);

    //Tercera Pagina
    _ItemsRequeridos[2].push_back(fabItems.crearItem(29));//Balde de Agua x 10
    _cantidadNecesaria[2].push_back(10);
    _ItemsRequeridos[2].push_back(fabItems.crearItem(49));//Cofre x 4
    _cantidadNecesaria[2].push_back(4);

    //Cuarta Pagina
    _ItemsRequeridos[3].push_back(fabItems.crearItem(8));//Espada de Diamante x 1
    _cantidadNecesaria[3].push_back(1);
    _ItemsRequeridos[3].push_back(fabItems.crearItem(53));//Mate
    _cantidadNecesaria[3].push_back(1);*/


    _ItemsRequeridos[0].push_back(fabItems.crearItem(10));//Palo x 100
    _cantidadNecesaria[0].push_back(1);

    _ItemsRequeridos[1].push_back(fabItems.crearItem(10));//Palo x 100
    _cantidadNecesaria[1].push_back(1);

    _ItemsRequeridos[2].push_back(fabItems.crearItem(10));//Palo x 100
    _cantidadNecesaria[2].push_back(1);

    _ItemsRequeridos[3].push_back(fabItems.crearItem(10));//Palo x 100
    _cantidadNecesaria[3].push_back(1);

    sf::Text textoDefaultExigencias;
    textoDefaultExigencias.setFont(fuente);
    textoDefaultExigencias.setCharacterSize(8);
    textoDefaultExigencias.setString("SIN DATOS");
    textoDefaultExigencias.setColor(sf::Color::Black);

    sf::RectangleShape subRayadoDefault;
    subRayadoDefault.setFillColor(sf::Color::Red);
    subRayadoDefault.setRotation(1);
    subRayadoDefault.setScale(0.001,1);

    for (int x = 0; x < 4; x++)
    {
        for (int i = 0; i < _cantidadNecesaria[x].size(); i++)
        {
            _textoExigencia[x].push_back(textoDefaultExigencias);//de esta forma logro que se agreguen el numero de "_cantidades nesesarias" nesesarias
            _selectoresItems[x].push_back(SeleccionRectangulo());//...y de igual forma lo hago con los selectes
            _lineaSubRayado[x].push_back(subRayadoDefault);//...y los subrayados
        }
    }
}

void InterfazBarcoHuida::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(_sprfondoInterfaz, states);
    target.draw(_textoTitulo, states);

    for (auto& itemAnalizado : _ItemsRequeridos[_pagina])
    {
        target.draw(*itemAnalizado,states);
    }

    int fila = 0;
    for (auto& textoExigenciaAnalizado : _textoExigencia[_pagina])
    {
        target.draw(textoExigenciaAnalizado,states);
        if (_cantidadNecesaria[_pagina][fila] == 0) target.draw(_lineaSubRayado[_pagina][fila],states);
        fila++;
    }

    if (!_oculto)target.draw(_bordeSeleccion);

    target.draw(_sprBotonPagSiguiente,states);
    target.draw(_sprBotonPagAnterior,states);

}

bool InterfazBarcoHuida::getCompletado()
{
    return _completado;
}

bool InterfazBarcoHuida::getOculto()
{
    return _oculto;
}

void InterfazBarcoHuida::setOculto(bool nuevoEstado)
{
    _oculto = nuevoEstado;
}

void InterfazBarcoHuida::setVolumen (float Volumen)
{
    _sonidoLapiz.setVolume(Volumen);
}

void InterfazBarcoHuida::update(const sf::Vector2f& posGlobalDelMouse, InventarioInterfaz& inventarioJugador)
{

    Comandos& input = Comandos::getInstancia();
    bool interaccionRealizada = false; // Con esta variable evito un click fantasma

    ///CONTROL BOTONES DE PAGINA
    if (_botonDerControlPagina.estaDentro(posGlobalDelMouse.x,posGlobalDelMouse.y,true))
    {
        if (input.mouseIzqRecienPresionado)
        {
            if (_pagina < 3) _pagina++;
            else _pagina = 0;
            interaccionRealizada = true;
        }
        _sprBotonPagSiguiente.setColor(sf::Color(255,255,255,255));
    }
    else
    {
        _sprBotonPagSiguiente.setColor(sf::Color(255,255,255,50));
    }

    if ((!interaccionRealizada) && (_botonIzqControlPagina.estaDentro(posGlobalDelMouse.x,posGlobalDelMouse.y,true)))
    {
        if (input.mouseIzqRecienPresionado)
        {
            if (_pagina > 0) _pagina--;
            else _pagina = 3;
            interaccionRealizada = true;
        }
        _sprBotonPagAnterior.setColor(sf::Color(255,255,255,255));
    }
    else
    {
        _sprBotonPagAnterior.setColor(sf::Color(255,255,255,50));
    }

    _textoTitulo.setString(_titulos[_pagina]);

    if (!interaccionRealizada)
    {

        ///ANALISIS DE LOS SELECTORES
        int fila = 0;
        bool sobreUno = false;
        int requisitosCompletos = 0;
        for (auto& itemAnalizado : _ItemsRequeridos[_pagina])
        {
            if (_cantidadNecesaria[_pagina][fila] > 0)
            {
                if (inventarioJugador.buscarItems(itemAnalizado -> getID()) != -1)
                {
                    itemAnalizado -> setColor(sf::Color(255,255,255,255));
                    if (_selectoresItems[_pagina][fila].estaDentro(posGlobalDelMouse.x,posGlobalDelMouse.y,true))
                    {
                        sobreUno = true;
                        _bordeSeleccion.setPosition(_selectoresItems[_pagina][fila].get_x1(),_selectoresItems[_pagina][fila].get_y1());

                        ///SISTEMA PARA QUITAR ITEM
                        if (input.mouseIzqRecienPresionado)
                        {
                            // 1. Datos iniciales
                            int idItem = itemAnalizado->getID();
                            int faltaParaCompletar = _cantidadNecesaria[_pagina][fila];
                            int tengoEnInventario = inventarioJugador.buscarTotalItems(idItem); // Usar la funci¢n nueva que suma todo

                            int cantidadAQuitar = 0;

                            // 2. L¢gica de c lculo blindada
                            if (input.teclaTomarTodo)
                            {
                                // NUNCA debe ser mayor a 'faltaParaCompletar' ni mayor a 'tengoEnInventario'
                                cantidadAQuitar = std::min(faltaParaCompletar, tengoEnInventario);
                            }
                            else
                            {
                                // Click normal: 1 a 1
                                if (tengoEnInventario >= 1)
                                {
                                    cantidadAQuitar = 1;
                                }
                            }

                            // 3. DEBUG: Ver qu‚ est  calculando antes de ejecutar
                            cout << "Calculo: Falta " << faltaParaCompletar
                                 << " | Tengo " << tengoEnInventario
                                 << " | A Quitar " << cantidadAQuitar << endl;

                            // 4. Ejecuci¢n segura
                            if (cantidadAQuitar > 0)
                            {
                                // IMPORTANTE: Pasamos expl¡citamente 'cantidadAQuitar'
                                if (inventarioJugador.quitarItem(idItem, cantidadAQuitar))
                                {
                                    _cantidadNecesaria[_pagina][fila] -= cantidadAQuitar;

                                    // Sonido y feedback
                                    if (_cantidadNecesaria[_pagina][fila] == 0) _sonidoLapiz.play();
                                    cout << "EXITO: Se quitaron " << cantidadAQuitar << " items." << endl;
                                }
                            }
                        }
                    }
                }
                else
                {
                    itemAnalizado -> setColor(sf::Color(255,255,255,50));
                }
            }
            else
            {
                itemAnalizado -> setColor(sf::Color(255,255,255,50));
                sf::Vector2f escalaSubRayado = _lineaSubRayado[_pagina][fila].getScale();
                lerp(escalaSubRayado, {1,1},0.05);
                _lineaSubRayado[_pagina][fila].setScale(escalaSubRayado);
                requisitosCompletos++;
            }
            fila++;
        }

        if (fila == requisitosCompletos)
        {
            _paginaCompletada[_pagina] = true;
        }

        if(!sobreUno)
        {
            _bordeSeleccion.setPosition(0,0);
        }

        ///Defino el estado de _completado
        int paginasCompletadas = 0;
        for (int i = 0; i < 4; i++)
        {
            if (_paginaCompletada[i] == true) paginasCompletadas++;
        }
        if (paginasCompletadas == 4) _completado = true;
    }
}

void InterfazBarcoHuida::ajustarEscalaAutomaticamente(const sf::View& vista, const float& relacionAspecto)
{
    // Escala proporcional al tamanio de la vista
    sf::Vector2f escalaCartel(sf::Vector2f(vista.getSize().x/512, vista.getSize().y/512 * relacionAspecto));

    float centroX = ((_sprfondoInterfaz.getGlobalBounds().width/ 2)) * escalaCartel.x;

    // Calcula posiciones

    sf::Vector2f posicionCartel;

    if(!_oculto) posicionCartel = sf::Vector2f(vista.getCenter().x - centroX, vista.getCenter().y- vista.getSize().y/2.5);
    else posicionCartel = sf::Vector2f(vista.getCenter().x - centroX, vista.getCenter().y + vista.getSize().y);

    ///SETEADO DEL TRANSFORM
    setPosition(posicionCartel);
    setScale(escalaCartel);


    _textoTitulo.setPosition(127 - _textoTitulo.getGlobalBounds().width / 2, 40);


    ///SETEADO DE LAS DIMENCIONES DE LOS BOTONES SigPag y PagAnterior

    _sprBotonPagAnterior.setPosition(5,37);
    _sprBotonPagSiguiente.setPosition(229,37);

    float botonIzqX1 = getPosition().x + (5  * getScale().x);
    float botonIzqX2 = getPosition().x + (28 * getScale().x);
    float botonIzqY1 = getPosition().y + (37 * getScale().y);
    float botonIzqY2 = getPosition().y + (60 * getScale().y);

    _botonIzqControlPagina.set_dimenciones( botonIzqX1, botonIzqX2, botonIzqY1, botonIzqY2);

    float botonDerX1 = getPosition().x + (229  * getScale().x);
    float botonDerX2 = getPosition().x + (252  * getScale().x);
    float botonDerY1 = getPosition().y + (37   * getScale().y);
    float botonDerY2 = getPosition().y + (60   * getScale().y);

    _botonDerControlPagina.set_dimenciones( botonDerX1, botonDerX2, botonDerY1, botonDerY2);

    int fila = 0;
    float selecItemX1, selecItemX2, selecItemY1, selecItemY2;
    for (auto& itemAnalizado : _ItemsRequeridos[_pagina])
    {
        ///posicion de los items
        itemAnalizado -> setPosition(48,88 + fila*4 + fila*28);
        itemAnalizado -> setEscala({0.9,0.9});

        ///Dimenciones de los selectores
        selecItemX1 = getPosition().x + 33*getScale().x;
        selecItemX2 = getPosition().x + 222*getScale().x;
        selecItemY1 = getPosition().y + 74*getScale().y + fila*2 + fila*28*getScale().y;
        selecItemY2 = getPosition().y + 74*getScale().y + fila*2 + (fila+1)*28*getScale().y;
        _selectoresItems[_pagina][fila].set_dimenciones(selecItemX1, selecItemX2, selecItemY1, selecItemY2);

        ///Dimensiones de los subRayados
        _lineaSubRayado[_pagina][fila].setSize({200, 2});
        _lineaSubRayado[_pagina][fila].setPosition(30,88 + fila*4 + fila*28);

        fila++;
    }
    ///ajustamos el borde que remarca el selector seleccionado
    _bordeSeleccion.setSize({selecItemX2-selecItemX1, selecItemY2-selecItemY1});

    fila = 0;
    for (auto& textoExigenciaAnalizado : _textoExigencia[_pagina])
    {
        string texto = "Faltan x";
        texto += std::to_string(_cantidadNecesaria[_pagina][fila]);
        textoExigenciaAnalizado.setString(texto);
        textoExigenciaAnalizado.setPosition(215 - textoExigenciaAnalizado.getGlobalBounds().width, 86 + fila*32);
        fila++;
    }
}

const std::vector<int>& InterfazBarcoHuida::getCantidadesPagina(int pagina) const
{
    return _cantidadNecesaria[pagina];
}

void InterfazBarcoHuida::setCantidadesPagina(int pagina, const std::vector<int>& datosCargados)
{
    if (pagina >= 0 && pagina < 4)
    {
        _cantidadNecesaria[pagina] = datosCargados;
    }
}

void InterfazBarcoHuida::recalcularEstadoCompletado()
{
    // Revisamos las 4 páginas
    int paginasOK = 0;
    for (int p = 0; p < 4; p++)
    {
        bool pagCompleta = true;
        // Revisamos cada item de la página
        for (int cantidad : _cantidadNecesaria[p])
        {
            if (cantidad > 0)
            {
                pagCompleta = false;
                break;
            }
        }
        _paginaCompletada[p] = pagCompleta;
        if (pagCompleta) paginasOK++;
    }

    _completado = (paginasOK == 4);
}

