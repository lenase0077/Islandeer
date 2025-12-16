#include "InterfazCamaPeticiones.h"
#include "Comando.h"
#include "funcionesInterpolacion.h"
#include <iostream>


using namespace std;

InterfazCamaPeticiones::InterfazCamaPeticiones(const sf::Texture& texturaFondoInterfaz, const sf::Font& fuente, FabricaItems& fabItems)
{
    _texturaFondoInterfaz = &texturaFondoInterfaz;
    _sprfondoInterfaz.setTexture(texturaFondoInterfaz);

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

    _titulos = "Kit de Construccion Naval";

    _textoTitulo.setFont(fuente);
    _textoTitulo.setColor(sf::Color::Black);
    _textoTitulo.setCharacterSize(8);

    _ItemsRequeridos.push_back(fabItems.crearItem(10));//Palo x 100
    _cantidadNecesaria.push_back(10);

    _ItemsRequeridos.push_back(fabItems.crearItem(13));//Palo x 100
    _cantidadNecesaria.push_back(2);



    sf::Text textoDefaultExigencias;
    textoDefaultExigencias.setFont(fuente);
    textoDefaultExigencias.setCharacterSize(8);
    textoDefaultExigencias.setString("SIN DATOS");
    textoDefaultExigencias.setColor(sf::Color::Black);

    sf::RectangleShape subRayadoDefault;
    subRayadoDefault.setFillColor(sf::Color::Red);
    subRayadoDefault.setRotation(1);
    subRayadoDefault.setScale(0.001,1);


    for (int i = 0; i < _cantidadNecesaria.size(); i++)
    {
        _textoExigencia.push_back(textoDefaultExigencias);//de esta forma logro que se agreguen el numero de "_cantidades nesesarias" nesesarias
        _selectoresItems.push_back(SeleccionRectangulo());//...y de igual forma lo hago con los selectes
        _lineaSubRayado.push_back(subRayadoDefault);//...y los subrayados
    }
}

void InterfazCamaPeticiones::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(_sprfondoInterfaz, states);
    target.draw(_textoTitulo, states);

    for (auto& itemAnalizado : _ItemsRequeridos)
    {
        target.draw(*itemAnalizado,states);
    }

    int fila = 0;
    for (auto& textoExigenciaAnalizado : _textoExigencia)
    {
        target.draw(textoExigenciaAnalizado,states);
        if (_cantidadNecesaria[fila] == 0) target.draw(_lineaSubRayado[fila],states);
        fila++;
    }

    if (!_oculto)target.draw(_bordeSeleccion);

}

bool InterfazCamaPeticiones::getCompletado()
{
    return _completado;
}

bool InterfazCamaPeticiones::getOculto()
{
    return _oculto;
}

void InterfazCamaPeticiones::setOculto(bool nuevoEstado)
{
    _oculto = nuevoEstado;
}

void InterfazCamaPeticiones::setVolumen (float Volumen)
{
    _sonidoLapiz.setVolume(Volumen);
}

void InterfazCamaPeticiones::update(const sf::Vector2f& posGlobalDelMouse, InventarioInterfaz& inventarioJugador)
{

    Comandos& input = Comandos::getInstancia();

    _textoTitulo.setString(_titulos);

    ///ANALISIS DE LOS SELECTORES
    int fila = 0;
    bool sobreUno = false;
    int requisitosCompletos = 0;
    for (auto& itemAnalizado : _ItemsRequeridos)
    {
        if (_cantidadNecesaria[fila] > 0)
        {
            if (inventarioJugador.buscarItems(itemAnalizado -> getID()) != -1)
            {
                itemAnalizado -> setColor(sf::Color(255,255,255,255));
                if (_selectoresItems[fila].estaDentro(posGlobalDelMouse.x,posGlobalDelMouse.y,true))
                {
                    sobreUno = true;
                    _bordeSeleccion.setPosition(_selectoresItems[fila].get_x1(),_selectoresItems[fila].get_y1());

                    ///SISTEMA PARA QUITAR ITEM
                    if (input.mouseIzqRecienPresionado)
                    {
                        // 1. Datos iniciales
                        int idItem = itemAnalizado->getID();
                        int faltaParaCompletar = _cantidadNecesaria[fila];
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
                                _cantidadNecesaria[fila] -= cantidadAQuitar;

                                // Sonido y feedback
                                if (_cantidadNecesaria[fila] == 0) _sonidoLapiz.play();
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
            sf::Vector2f escalaSubRayado = _lineaSubRayado[fila].getScale();
            lerp(escalaSubRayado, {1,1},0.05);
            _lineaSubRayado[fila].setScale(escalaSubRayado);
            requisitosCompletos++;
        }
        fila++;
    }

    if(!sobreUno)
    {
        _bordeSeleccion.setPosition(0,0);
    }

    if (fila == requisitosCompletos)
    {
        _completado = true;
    }

}

void InterfazCamaPeticiones::ajustarEscalaAutomaticamente(const sf::View& vista, const float& relacionAspecto)
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

    int fila = 0;
    float selecItemX1, selecItemX2, selecItemY1, selecItemY2;
    for (auto& itemAnalizado : _ItemsRequeridos)
    {
        ///posicion de los items
        itemAnalizado -> setPosition(48,88 + fila*4 + fila*28);
        itemAnalizado -> setEscala({0.9,0.9});

        ///Dimenciones de los selectores
        selecItemX1 = getPosition().x + 33*getScale().x;
        selecItemX2 = getPosition().x + 222*getScale().x;
        selecItemY1 = getPosition().y + 74*getScale().y + fila*2 + fila*28*getScale().y;
        selecItemY2 = getPosition().y + 74*getScale().y + fila*2 + (fila+1)*28*getScale().y;
        _selectoresItems[fila].set_dimenciones(selecItemX1, selecItemX2, selecItemY1, selecItemY2);

        ///Dimensiones de los subRayados
        _lineaSubRayado[fila].setSize({200, 2});
        _lineaSubRayado[fila].setPosition(30,88 + fila*4 + fila*28);

        fila++;
    }
    ///ajustamos el borde que remarca el selector seleccionado
    _bordeSeleccion.setSize({selecItemX2-selecItemX1, selecItemY2-selecItemY1});

    fila = 0;
    for (auto& textoExigenciaAnalizado : _textoExigencia)
    {
        string texto = "Faltan x";
        texto += std::to_string(_cantidadNecesaria[fila]);
        textoExigenciaAnalizado.setString(texto);
        textoExigenciaAnalizado.setPosition(215 - textoExigenciaAnalizado.getGlobalBounds().width, 86 + fila*32);
        fila++;
    }
}

