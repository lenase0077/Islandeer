#include "InterfazBarcoHuida.h"
#include "Comando.h"
#include <iostream>


using namespace std;

InterfazBarcoHuida::InterfazBarcoHuida(const sf::Texture& texturaFondoInterfaz, FabricaItems& fabItems){
    _texturaFondoInterfaz = &texturaFondoInterfaz;
    _sprfondoInterfaz.setTexture(texturaFondoInterfaz);

    _titulos[0] = "Kit de Construcci¢n Naval";
    _titulos[1] = "Suministros y Cocina";
    _titulos[2] = "Hidrataci¢n y Almacenamiento";
    _titulos[3] = "Seguridad y Salud Mental";

    ///FUENTE LOCAL TEMPORAL, NO SE ASUSTEN
    if (_fuenteTexto.getInfo().family == "") {
        if (!_fuenteTexto.loadFromFile("PIXEARG_.TTF")){
            cout << "Error al cargar PIXEARG_.TTF" << endl;
        }
        const_cast<sf::Texture&>(_fuenteTexto.getTexture(8)).setSmooth(false);
    }
    _textoTitulo.setFont(_fuenteTexto);
    _textoTitulo.setCharacterSize(8);

    ///Agregamos los requisitos
    //Primer pagina
    _ItemsRequeridos[0].push_back(fabItems.crearItem(52));//mesa de crafteo
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
    _cantidadNecesaria[3].push_back(1);


    sf::Text textoDefaultExigencias;
    textoDefaultExigencias.setFont(_fuenteTexto);
    textoDefaultExigencias.setCharacterSize(8);
    textoDefaultExigencias.setString("SIN DATOS");


    for (int x = 0; x < 4; x++){
           for (int i = 0; i < _cantidadNecesaria[x].size(); i++){
            _textoExigencia[x].push_back(textoDefaultExigencias);//de esta forma logro que se agreguen el numero de "_cantidades nesesarias" nesesarias
            _selectoresItems[x].push_back(SeleccionRectangulo());//...y de igual forma lo hago con los selectes
        }
    }
}

void InterfazBarcoHuida::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    states.transform *= getTransform();
    target.draw(_sprfondoInterfaz, states);
    target.draw(_textoTitulo, states);

    for (auto& itemAnalizado : _ItemsRequeridos[_pagina])
        {
            target.draw(*itemAnalizado,states);
        }

    for (auto& textoExigenciaAnalizado : _textoExigencia[_pagina]){
            target.draw(textoExigenciaAnalizado,states);
    }

}

void InterfazBarcoHuida::update(const sf::Vector2f& posGlobalDelMouse, InventarioInterfaz& inventarioJugador){

    Comandos& input = Comandos::getInstancia();

    if (_botonDerControlPagina.estaDentro(posGlobalDelMouse.x,posGlobalDelMouse.y,input.mouseIzqRecienPresionado)){
        if (_pagina < 3) _pagina++;
        else _pagina = 0;
    }
    else if (_botonIzqControlPagina.estaDentro(posGlobalDelMouse.x,posGlobalDelMouse.y,input.mouseIzqRecienPresionado)){
        if (_pagina > 0) _pagina--;
        else _pagina = 3;
    }

    _textoTitulo.setString(_titulos[_pagina]);

    ///ANALISIS DE LOS SELECTORES
    int fila = 0;
    bool sobreUno = false;
    for (auto& itemAnalizado : _ItemsRequeridos[_pagina])
    {
        itemAnalizado -> setPosition(48,88 + fila*32);
        if (_selectoresItems[_pagina][fila].estaDentro(posGlobalDelMouse.x,posGlobalDelMouse.y,true)){
            cout << "estas dentro del item" << itemAnalizado -> getTitulo() << endl;
            sobreUno = true;
        }
        fila++;
    }
    if(!sobreUno) cout << "NO estas dentro del item" << endl;;

}

void InterfazBarcoHuida::ajustarEscalaAutomaticamente(const sf::View& vista, const float& relacionAspecto){
    // Escala proporcional al tamanio de la vista
    sf::Vector2f escalaCartel(sf::Vector2f(vista.getSize().x/512, vista.getSize().y/512 * relacionAspecto));

    float centroX = ((_sprfondoInterfaz.getGlobalBounds().width/ 2)) * escalaCartel.x;

    // Calcula posiciones
    sf::Vector2f posicionCartel(vista.getCenter().x - centroX, vista.getCenter().y- vista.getSize().y/2.5);

    ///SETEADO DEL TRANSFORM
    setPosition(posicionCartel);
    setScale(escalaCartel);


    _textoTitulo.setPosition(127 - _textoTitulo.getGlobalBounds().width / 2, 40);


    ///SETEADO DE LAS DIMENCIONES DE LOS BOTONES SigPag y PagAnterior
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
            itemAnalizado -> setPosition(48,88 + fila*32);

            ///Dimenciones de los selectores
            selecItemX1 = getPosition().x + 33*getScale().x;
            selecItemX2 = getPosition().x + 222*getScale().x;
            selecItemY1 = getPosition().y + 74*getScale().y + fila*4 + fila*28*getScale().y;
            selecItemY2 = getPosition().y + 74*getScale().y + fila*4 + (fila+1)*28*getScale().y;
            _selectoresItems[_pagina][fila].set_dimenciones(selecItemX1, selecItemX2, selecItemY1, selecItemY2);
            fila++;
        }

    fila = 0;
    for (auto& textoExigenciaAnalizado : _textoExigencia[_pagina]){
        string texto = "Faltan x";
        texto += std::to_string(_cantidadNecesaria[_pagina][fila]);
        textoExigenciaAnalizado.setString(texto);
        textoExigenciaAnalizado.setPosition(215 - textoExigenciaAnalizado.getGlobalBounds().width, 86 + fila*32);
        fila++;
    }
}

