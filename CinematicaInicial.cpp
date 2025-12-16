#include "CinematicaInicial.h"
#include <cmath>
#include <iostream>
#include "funcionesInterpolacion.h"
using namespace std;

CinematicaInicial::CinematicaInicial(const sf::Texture& texturaPersonaje, const sf::Texture& texturaAvion , const sf::Texture& texturaTurbina, const sf::Texture& texturaNubes)
{
    _rectanguloCielo.setFillColor(sf::Color(99,155,255,255));
    _rectanguloCielo.setSize({1000,1000});

    _sprAvion.setTexture(texturaAvion);
    _sprAvion.setTextureRect({0,0,320,96});
    _sprAvion.setPosition(200,0);

    _sprPersonaje.setTexture(texturaPersonaje);
    _sprPersonaje.setTextureRect({0,4*32,32,32});
    _sprPersonaje.setOrigin(16,32);
    _sprPersonaje.setPosition(_sprAvion.getPosition().x + 176,_sprAvion.getPosition().y + 46);

    _sprAvionFondo.setTexture(texturaAvion);
    _sprAvionFondo.setTextureRect({320,0,320,96});
    _sprAvionFondo.setPosition(_sprAvion.getPosition());

    _sprNubes.setPosition(-100,0);

    _sprNubes.setTexture(texturaNubes);

    _sprTurbina.setTexture(texturaTurbina);
    _sprTurbina.setTextureRect({0,0,47,33});
    _sprTurbina.setOrigin(42,4);
    _sprTurbina.setPosition(_sprAvion.getPosition().x + 292,_sprAvion.getPosition().y + 82);
}
void CinematicaInicial::update()
{
    _incSeno += 0.01;
    _incSeno2 += 0.8;
    float centroYAvion = 16;
    if (_etapaAnimacion == 0){///EL AVION ESTA NORMAL
        if (_tiempoEnEtapa.getElapsedTime().asSeconds() < 5){
            _sprAvion.setPosition(_sprAvion.getPosition().x, centroYAvion + (sin(_incSeno) * 10));

            _sprAvionFondo.setPosition(_sprAvion.getPosition());

            _sprTurbina.setPosition(_sprAvion.getPosition().x + 292,_sprAvion.getPosition().y + 82);

            _sprPersonaje.setPosition(_sprAvion.getPosition().x + 176,_sprAvion.getPosition().y + 46);

            if (_sprNubes.getPosition().x < 700){
                    _sprNubes.setPosition(_sprNubes.getPosition().x + 1.8, _sprNubes.getPosition().y);
            }
            else{
                _sprNubes.setPosition(-100, 32 * (rand()%5) - 1);
            }
        }
        else{
                _etapaAnimacion++;
                _tiempoEnEtapa.restart();
        }
    }
    else if(_etapaAnimacion == 1){///LA TURBINA FALLA
            if (_tiempoEnEtapa.getElapsedTime().asSeconds() < 5){

                _sprAvion.setPosition(_sprAvion.getPosition().x, centroYAvion + (sin(_incSeno) * 10));

                _sprAvionFondo.setPosition(_sprAvion.getPosition());

                //sacudida de la turbina
                _sprTurbina.setPosition(_sprAvion.getPosition().x + 292 + (sin(_incSeno) * 4),_sprAvion.getPosition().y + 82 + (sin(_incSeno2) * 2));

                _sprPersonaje.setPosition(_sprAvion.getPosition().x + 176,_sprAvion.getPosition().y + 46);
                _sprPersonaje.setTextureRect({0,8*32,32,32});//personaje cambia exprecion

                if (_sprNubes.getPosition().x < 700){
                        _sprNubes.setPosition(_sprNubes.getPosition().x + 1.8, _sprNubes.getPosition().y);
                }
                else{
                    _sprNubes.setPosition(-100, 32 * (rand()%5) - 1);
                }
            }
            else{
                    _etapaAnimacion++;
                    _tiempoEnEtapa.restart();
            }

    }
    else if(_etapaAnimacion == 2){///El Jugador se asusta
            if (_tiempoEnEtapa.getElapsedTime().asSeconds() < 5){

                _sprAvion.setPosition(_sprAvion.getPosition().x, centroYAvion + (sin(_incSeno) * 10));

                _sprAvionFondo.setPosition(_sprAvion.getPosition());

                //sacudida de la turbina
                _sprTurbina.setPosition(_sprAvion.getPosition().x + 292 + (sin(_incSeno) * 4),_sprAvion.getPosition().y + 82 + (sin(_incSeno2) * 2));

                //personaje asustandose
                _sprPersonaje.setPosition(_sprAvion.getPosition().x + 176,_sprAvion.getPosition().y + 46 + (sin(_incSeno2) * 2));

                if (_sprNubes.getPosition().x < 700){
                        _sprNubes.setPosition(_sprNubes.getPosition().x + 1.8, _sprNubes.getPosition().y);
                }
                else{
                    _sprNubes.setPosition(-100, 32 * (rand()%5) - 1);
                }
            }
            else{
                    _etapaAnimacion++;
                    _tiempoEnEtapa.restart();
            }

    }
    else if(_etapaAnimacion == 3){///La turbina cae y el avion desacelera
            if (_tiempoEnEtapa.getElapsedTime().asSeconds() < 6){
                lerp(_movimientoAvion, 0, 0.02);

                _sprAvion.setPosition(_sprAvion.getPosition().x, centroYAvion + (sin(_incSeno) * 10 * _movimientoAvion));

                _sprAvionFondo.setPosition(_sprAvion.getPosition());

                //sacudida de la turbina
                _sprTurbina.setPosition(_sprTurbina.getPosition().x + 0.8,_sprTurbina.getPosition().y + 0.2 );
                _sprTurbina.setRotation(-45);

                //personaje asustandose
                _sprPersonaje.setPosition(_sprAvion.getPosition().x + 176,_sprAvion.getPosition().y + 46 + (sin(_incSeno2) * 2 * _movimientoAvion));

                if (_sprNubes.getPosition().x < 700){
                        _sprNubes.setPosition(_sprNubes.getPosition().x + 1.8 * _movimientoAvion, _sprNubes.getPosition().y);
                }
                else{
                    _sprNubes.setPosition(-100, 32 * (rand()%5) - 1);
                }
            }
            else{
                    _etapaAnimacion++;
                    _tiempoEnEtapa.restart();
            }

    }
    else if(_etapaAnimacion == 4){///El avion cae y el personaje grita
            if (_tiempoEnEtapa.getElapsedTime().asSeconds() < 10){
                lerp(_movimientoAvion, 0, 0.02);

                _sprAvion.setPosition(_sprAvion.getPosition().x, _sprAvion.getPosition().y + 3);

                _sprAvionFondo.setPosition(_sprAvion.getPosition());

                //personaje asustandose
                _sprPersonaje.setPosition(_sprAvion.getPosition().x + 176,_sprAvion.getPosition().y + 46 + (sin(_incSeno2) * 2));

                if (_sprNubes.getPosition().x < 700){
                        _sprNubes.setPosition(_sprNubes.getPosition().x + 1.8 * _movimientoAvion, _sprNubes.getPosition().y);
                }
                else{
                    _sprNubes.setPosition(-100, 32 * (rand()%5) - 1);
                }
            }
            else{
                    _etapaAnimacion++;
                    _tiempoEnEtapa.restart();
                    ///FINAL
                    _completado = true;
                    _reproducir = false;
            }

    }


    /*
    else{
        cout << "Completado" << endl;
        _reproducir = false;
        _completado = true;
    }*/

}
void CinematicaInicial::ajustarEscalaAutomaticamente(const sf::View& vista, const float& relacionAspecto)
{
    sf::Vector2f escalaCinematica(sf::Vector2f(vista.getSize().x/512, vista.getSize().y/512 * relacionAspecto));

    // Calcula posiciones
    sf::Vector2f posicionCinematica;
    posicionCinematica = sf::Vector2f(vista.getCenter().x-vista.getSize().x/2, vista.getCenter().y - vista.getSize().y/2);

     ///SETEADO DEL TRANSFORM
    setPosition(posicionCinematica);
    setScale(escalaCinematica);
}

void CinematicaInicial::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw( _rectanguloCielo,states);
    target.draw( _sprNubes,states);
    target.draw( _sprAvionFondo,states);
    target.draw( _sprPersonaje,states);
    target.draw( _sprAvion,states);
    target.draw( _sprTurbina,states);
}

bool CinematicaInicial::getCompletado()
{
    return _completado;
}
bool CinematicaInicial::estaReproduciendo()
{
    return _reproducir;
}
void CinematicaInicial::reproducir(){
    _reproducir = true;
}
