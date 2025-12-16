#include "CinematicaFinal.h"
#include <cmath>
#include <iostream>
using namespace std;

CinematicaFinal::CinematicaFinal(const sf::Texture& texturaPersonaje, const sf::Texture& texturaBarco, const sf::Texture& texturaAgua, const sf::Font& fuenteTexto, const std::string textoCreditos)
{
    _textoCreditos.setFont(fuenteTexto);
    _textoCreditos.setString(textoCreditos);
    _textoCreditos.setCharacterSize(8);
    _textoCreditos.setScale(1.8,1.8);
    _textoCreditos.setPosition(200,0);
    _textoCreditos.setColor(sf::Color::Black);

    _barco.setTexture(texturaBarco);
    _barco.setPosition( 10, -335);

    _personaje.setTexture(texturaPersonaje);
    _personaje.setTextureRect({0,0,32,32});
    _personaje.setOrigin(16,32);

    _rectanguloAgua.setSize({1000.0,2000.0});
    _rectanguloAgua.setPosition(0,-500);
    _rectanguloAgua.setTexture(&texturaAgua);
    _rectanguloAgua.setTextureRect(sf::IntRect(0, 0, _rectanguloAgua.getSize().x, _rectanguloAgua.getSize().y));

    string Lecturadescripcion = "";
    string desbordePostEspacio = "";
    string stringCreditos = textoCreditos;
    int anchoMax = 200;

    ///PONEMOS LOS SALTOS EN EL TEXTO
    int PosicionUltimoEspacio = 0;
    for (int i = 0 ; i < stringCreditos.size() ; i++){
        char caracter = stringCreditos[i];

        if (caracter == ' '){
            PosicionUltimoEspacio = i;
            desbordePostEspacio = "";
        }

        ///Agregamos caracter por caracter
        Lecturadescripcion += caracter;
        desbordePostEspacio += caracter;

        _textoCreditos.setString(Lecturadescripcion);

        ///Si se pasa del ancho maximo -> \n
        if (_textoCreditos.getLocalBounds().width >= anchoMax && caracter!='\n'){
            stringCreditos[PosicionUltimoEspacio] = '\n';

            Lecturadescripcion = desbordePostEspacio;
        }
    }

    _textoCreditos.setString(stringCreditos);

}
void CinematicaFinal::update()
{
    _incSeno += 0.01;
    if (_textoCreditos.getPosition().y > _limiteTexto){
        cout << "limite de texto Y:" << _limiteTexto << endl;
        _textoCreditos.setPosition(_textoCreditos.getPosition().x, _textoCreditos.getPosition().y - 0.8);
        _rectanguloAgua.setPosition(0,_rectanguloAgua.getPosition().y - 0.5);
        _barco.setPosition(10 + (std::sin(_incSeno) * 6), _barco.getPosition().y);
        _personaje.setPosition(_barco.getPosition().x + 79, _barco.getPosition().y + 212 );
    }
    else{
        cout << "Completado" << endl;
        _reproducir = false;
        _completado = true;
    }

}
void CinematicaFinal::ajustarEscalaAutomaticamente(const sf::View& vista, const float& relacionAspecto)
{
    sf::Vector2f escalaCinematica(sf::Vector2f(vista.getSize().x/512, vista.getSize().y/512 * relacionAspecto));

    // Calcula posiciones
    sf::Vector2f posicionCinematica;
    posicionCinematica = sf::Vector2f(vista.getCenter().x-vista.getSize().x/2, vista.getCenter().y + vista.getSize().y/2);

     ///SETEADO DEL TRANSFORM
    setPosition(posicionCinematica);
    setScale(escalaCinematica);

    _limiteTexto = ((vista.getCenter().y - vista.getSize().y/2) - posicionCinematica.y )/ escalaCinematica.y  - (_textoCreditos.getGlobalBounds().height + 16);
}

void CinematicaFinal::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(_rectanguloAgua,states);
    target.draw(_barco,states);
    target.draw(_personaje,states);
    target.draw(_textoCreditos,states);
}

bool CinematicaFinal::getCompletado()
{
    return _completado;
}
bool CinematicaFinal::estaReproduciendo()
{
    return _reproducir;
}
void CinematicaFinal::reproducir(){
    _reproducir = true;
}
