#include <iostream>
#include "Personaje.h"
#include "Funciones.h"
#include <cmath>

using namespace std;

bool Personaje::getEstaCorriendo() const {
    return _estaCorriendo;
}

void Personaje::setEstaCorriendo(bool EstaCorriendo) {
    _estaCorriendo = EstaCorriendo;
}

Personaje::Personaje()
    :
    _velocidad(0,0),
    _movimiento(1),
    _frameActual(0),
    _vida (100),
    _vidaMaxima(100),
    _energia(100),
    _barraVida(_vida, _vidaMaxima) {

    if (!_textura.loadFromFile("Basic Charakter Spritesheet.png")) {
        std::cout << "Error cargando textura" << std::endl;
    }

    _sprite.setTexture(_textura);
    setPosition(10, 10);

    // Si tu spritesheet tiene frames chicos, definí un rectángulo inicial
    _sprite.setTextureRect(sf::IntRect(0, 0, 16, 16)); // primer frame 32x32

    _colision.setColision(getColisionBounds());

    if (!_footprintsBuffer.loadFromFile("walk-on-grass-3-291986.wav")) {
        return;
    }

    _footprints.setBuffer(_footprintsBuffer);
    _footprints.setVolume(3.f);
    _footprints.setLoop(true);

}

Personaje::Personaje(int alto, int ancho)
    : _velocidad(0,0), _movimiento(1), _frameActual(0) {

    if (!_textura.loadFromFile("Basic Charakter Spritesheet.png")) {
        std::cout << "Error cargando textura" << std::endl;
    }

    _sprite.setOrigin(0,0);
    _sprite.setTexture(_textura);
    _sprite.setPosition(alto, ancho);

    // Si tu spritesheet tiene frames chicos, definí un rectángulo inicial
    _sprite.setTextureRect(sf::IntRect(0, 0, 16, 16)); // primer frame 32x32
    _colision.setColision(_sprite.getGlobalBounds());
}

void Personaje::setVida(float vida) {
    _vida = vida;
}

float Personaje::getVida() {
    return _vida;
}


void Personaje::animar() {
    ///Verificamos si hay movimiento
    if (abs(_velocidad.x) > 0.f || abs(_velocidad.y) > 0.f) {

        ///Verificamos si ya paso mas de 100 milisegundos
        if (_animacion.getElapsedTime().asMilliseconds() > 200) {

            ///Avanzamos al siguiente frame
            if (_frameActual == 2) {
                _frameActual = 3;
            } else _frameActual = 2;

            ///Reiniciamos el reloj
            _animacion.restart();
        }
    }

    ///Cuando no hay movimiento
    else {

        ///Si el personaje esta en movimiento, hacemos que cambie al frame 0
        if (_frameActual == 2 || _frameActual == 3) {
            _frameActual = 0;
        }

        else if (_animacion.getElapsedTime().asMilliseconds() > 300) {
            if (_frameActual == 0) {
                _frameActual = 1;
            }

            else _frameActual = 0;

            _animacion.restart();
        }
    }

    setFrame( _movimiento, _frameActual, _sprite);
}

void Personaje::draw(sf::RenderTarget& target, sf::RenderStates states) const {

    states.transform *= getTransform();
    target.draw(_sprite, states);
    target.draw(_espada);
    target.draw(_barraVida);
}

void Personaje::cmd() {

    _velocidad = sf::Vector2f(0.f,0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        _velocidad.x = -1.5;
        _movimiento = 2;
    };

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        _velocidad.x = 1.5;
        _movimiento = 3;
    };

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        _velocidad.y = -1.5;
        _movimiento = 1;
    };

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        _velocidad.y = 1.5;
        _movimiento = 0;
    };

    if (_velocidad.x != 0.f && _velocidad.y != 0.f) {
        _velocidad /= sqrt(2.f);
    }

    Correr(_velocidad);
}

void Personaje::actuarEnBaseALaColision (string IDColision) {

    if (IDColision == "Enemy") {
        _tocoEnemigo = true;
        setVida(getVida()-1);
    }

    else if (IDColision == "Animal")
    {
        _tocoEnemigo = false;
    }

    else {
        _tocoEnemigo = false;
        _velocidad = {0.f, 0.f};
    }
}

void Personaje::chocar(Colisionador& colision) {

    sf::FloatRect RectanguloColison = getColisionBounds();
    RectanguloColison.left += _velocidad.x;
    RectanguloColison.top += _velocidad.y;

    if (RectanguloColison.intersects(colision.getColision())) {

        actuarEnBaseALaColision(colision.getID());
    }

    ///Actualizamos la colision
    _colision.setColision(getColisionBounds());
}

void Personaje::update() {
    _sprite.setScale(1.0f, 1.0f);

    animar();
    manejarPasos();
    move(_velocidad);
    _barraVida.setPosition(getPosition().x, getPosition().y - 10);
    _barraVida.actualizar();

}

void Personaje::limite() {
    if (_sprite.getPosition().x > 1024) {
        _sprite.setPosition(0, _sprite.getPosition().y);
    }

    if (_sprite.getPosition().x < 0) {
        _sprite.setPosition(1024, _sprite.getPosition().y);
    }

    if (_sprite.getPosition().y > 768) {
        _sprite.setPosition(_sprite.getPosition().x, 0);
    }

    if (_sprite.getPosition().y < 0) {
        _sprite.setPosition(_sprite.getPosition().x, 768);
    }


//    _colision.setColision(_sprite.getGlobalBounds());

//    _colision.setColision(sf::FloatRect(_sprite.getGlobalBounds().left, _sprite.getGlobalBounds().top, (_sprite.getGlobalBounds().width)-100, (_sprite.getGlobalBounds().height)-100));
    _colision.setColision(_sprite.getGlobalBounds());
//    _colision.setColision(tamanio);

}

sf::Vector2f Personaje::getPosition() const {
    return sf::Transformable::getPosition();
}

void Personaje::setVelocidad(float vx, float vy) {
    _velocidad.x = vx;
    _velocidad.y = vy;
}

void Personaje::Correr(sf::Vector2f& velocidad) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
        if (!_energia == 0) {
            velocidad *= 1.5f;
            setEstaCorriendo(true);
            if ((_animacion.getElapsedTime().asMilliseconds() > 100)) {
                _energia -= 10.f;
            }
        }

    } else {

        setEstaCorriendo(false);
        if ((_animacion.getElapsedTime().asMilliseconds() > 100))
        {
            _energia += 10;
        }


        };
}

void Personaje::manejarPasos() {


    bool estaMoviendo = abs(_velocidad.x) > 0 || abs(_velocidad.y) > 0;

    if (estaMoviendo) {
        if (_relojPasos.getElapsedTime().asMilliseconds() > 100) {
            if (_footprints.getStatus() != sf::Sound::Playing) {
                _footprints.play();
            }
        }
    }

    else if (_footprints.getStatus() == sf::Sound::Playing) {
        _footprints.stop();
    }
}

sf::FloatRect Personaje::getColisionBounds() const {

    sf::FloatRect localRect = _sprite.getLocalBounds();

    return getTransform().transformRect(localRect);

}

void Personaje::setPosicion(float uno, float dos) {
    setPosition(uno, dos);
}


////Espada

void Personaje::updateEspada(const Raton& mouse) {
    _espada.update(mouse.getPosicion(), getPosition());
}


