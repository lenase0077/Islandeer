#include <iostream>
#include "Personaje.h"
#include "Funciones.h"
#include "Comando.h"
#include <cmath>
using namespace std;

bool Personaje::getEstaCorriendo() const
{
    return _estaCorriendo;
}

void Personaje::setEstaCorriendo(bool EstaCorriendo)
{
    _estaCorriendo = EstaCorriendo;
}

Personaje::Personaje(sf::Texture& _textura)
    :
    _velocidad(0,0),
    _movimiento(1),
    _frameActual(0),
    _vida (100),
    _vidaMaxima(100),
    _energia(100),
    _barraVida(_vida, _vidaMaxima)
{

    _sprite.setTexture(_textura);
    setPosition(10, 10);

    // Si tu spritesheet tiene frames chicos, defin� un rect�ngulo inicial
    _sprite.setTextureRect(sf::IntRect(0, 0, 32, 32)); // primer frame 32x32

    _colision.setColision(getColisionBounds());

    if (!_footprintsBuffer.loadFromFile("walk-on-grass-3-291986.wav"))
    {
        return;
    }

    _footprints.setBuffer(_footprintsBuffer);
    _footprints.setVolume(3.f);
    _footprints.setLoop(true);

}

Personaje::Personaje(sf::Texture& _textura, int alto, int ancho)
    : _velocidad(0,0), _movimiento(1), _frameActual(0)
{

    _sprite.setOrigin(0,0);
    _sprite.setTexture(_textura);
    _sprite.setPosition(alto, ancho);

    // Si tu spritesheet tiene frames chicos, defin� un rect�ngulo inicial
    _sprite.setTextureRect(sf::IntRect(0, 0, 32, 32)); // primer frame 32x32
    _colision.setColision(_sprite.getGlobalBounds());
}

void Personaje::setVida(float vida)
{
    _vida = vida;
}

float Personaje::getVida()
{
    return _vida;
}

void Personaje::animarPersonaje()
{
    ///Verificamos si hay movimiento
    if (abs(_velocidad.x) > 0.f || abs(_velocidad.y) > 0.f)
    {

        ///Verificamos si ya paso mas de 100 milisegundos
        if (_animacion.getElapsedTime().asMilliseconds() > 200)
        {

            ///Avanzamos al siguiente frame
            if (_frameActual == 2)
            {
                _frameActual = 3;
            }
            else _frameActual = 2;

            ///Reiniciamos el reloj
            _animacion.restart();
        }
    }

    ///Cuando no hay movimiento
    else
    {

        ///Si el personaje esta en movimiento, hacemos que cambie al frame 0
        if (_frameActual == 2 || _frameActual == 3)
        {
            _frameActual = 0;
        }

        else if (_animacion.getElapsedTime().asMilliseconds() > 300)
        {
            if (_frameActual == 0)
            {
                _frameActual = 1;
            }

            else _frameActual = 0;

            _animacion.restart();
        }
    }

    setFramePersonaje( _movimiento, _frameActual, _sprite);
}

void Personaje::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    if (_movimiento == 1)
    {
        if (_tieneHerramienta && _atacando)
        {
            target.draw(_spriteHerramienta, states);
        }
        target.draw(_sprite, states);
    }
    else
    {
        target.draw(_sprite, states);
        if (_tieneHerramienta && _atacando)
        {
            target.draw(_spriteHerramienta, states);
        }
    }
//    target.draw(_espada);
    target.draw(_barraVida);
}

void Personaje::cmd(float deltatime)
{

    _velocidad = sf::Vector2f(0.f,0.f);
    Comandos& input = Comandos::getInstancia();

    if (input.teclaIzquierda)
    {
        _velocidad.x = -1.5;
        _movimiento = 2;
    };

    if (input.teclaDerecha)
    {
        _velocidad.x = 1.5;
        _movimiento = 3;
    };

    if (input.teclaArriba)
    {
        _velocidad.y = -1.5;
        _movimiento = 1;
    };

    if (input.teclaAbajo)
    {
        _velocidad.y = 1.5;
        _movimiento = 0;
    };
    if (_velocidad.x != 0.f && _velocidad.y != 0.f)
    {
        _velocidad /= sqrt(2.f);
    }



    Correr(_velocidad, deltatime);
}

void Personaje::actuarEnBaseALaColision (string IDColision)
{

    if (IDColision == "Enemy")
    {
        _tocoEnemigo = true;
        setVida(getVida()-1);
    }

    else if (IDColision == "Animal")
    {
        _tocoEnemigo = false;

    }

    else
    {
        _tocoEnemigo = false;
        _velocidad = {0.f, 0.f};
    }
}

void Personaje::chocar(Colisionador& colision)
{

    sf::FloatRect RectanguloColison = getColisionBounds();
    RectanguloColison.left += _velocidad.x;
    RectanguloColison.top += _velocidad.y;

    if (RectanguloColison.intersects(colision.getColision()))
    {

        actuarEnBaseALaColision(colision.getID());
    }

    ///Actualizamos la colision
    _colision.setColision(getColisionBounds());
}

void Personaje::update(float deltatime)
{
    _sprite.setScale(1.0f, 1.0f);

    animarPersonaje();
    manejarPasos();
    move(_velocidad);


    if (_movimiento == 2)
    {
        _spriteHerramienta.setScale(-1, 1);
        _spriteHerramienta.setPosition(8, 16);
    }
    else if (_movimiento == 1)
    {
        _spriteHerramienta.setScale(1, 1);
        _spriteHerramienta.setPosition(16, 8);
    }
    else if (_movimiento == 0)
    {
        _spriteHerramienta.setScale(1, 1);
        _spriteHerramienta.setPosition(16, 32);
    }
    else
    {
        _spriteHerramienta.setScale(1, 1);
        _spriteHerramienta.setPosition(24, 16);
    }


    actualizarAnimacionAtaque(deltatime);

    _barraVida.setPosition(getPosition().x, getPosition().y - 10);
    _barraVida.actualizar();



}

void Personaje::limite()
{
    if (_sprite.getPosition().x > 1024)
    {
        _sprite.setPosition(0, _sprite.getPosition().y);
    }

    if (_sprite.getPosition().x < 0)
    {
        _sprite.setPosition(1024, _sprite.getPosition().y);
    }

    if (_sprite.getPosition().y > 768)
    {
        _sprite.setPosition(_sprite.getPosition().x, 0);
    }

    if (_sprite.getPosition().y < 0)
    {
        _sprite.setPosition(_sprite.getPosition().x, 768);
    }


//    _colision.setColision(_sprite.getGlobalBounds());

//    _colision.setColision(sf::FloatRect(_sprite.getGlobalBounds().left, _sprite.getGlobalBounds().top, (_sprite.getGlobalBounds().width)-100, (_sprite.getGlobalBounds().height)-100));
    _colision.setColision(_sprite.getGlobalBounds());
//    _colision.setColision(tamanio);

}

sf::Vector2f Personaje::getPosition() const
{
    return sf::Transformable::getPosition();
}

void Personaje::setVelocidad(float vx, float vy)
{
    _velocidad.x = vx;
    _velocidad.y = vy;
}

float Personaje::getEnergia()
{
    return _energia;
}

void Personaje::Correr(sf::Vector2f& velocidad, float deltatime)
{
    Comandos& input = Comandos::getInstancia();

    bool hayMovimiento = (abs(_velocidad.x) > 0.f || abs(_velocidad.y) > 0.f);
    bool estacorriendo = input.teclaCorrer && _energia > 0 && hayMovimiento;

    if (estacorriendo)
    {
        velocidad *= 1.5f;
        setEstaCorriendo(true);
    }
    else
    {
        setEstaCorriendo(false);
    }

    _acumuladorEnergia += deltatime;

    if (_acumuladorEnergia >= 500)
    {
        if (getEstaCorriendo())
        {
            _energia -= 10.f;

            if (_energia < 0)
            {
                _energia = 0;
            }
        }

        else
        {
            _energia += 10.f;

            if (_energia > 100)
            {
                _energia = 100;
            }
        }
        _acumuladorEnergia = 0;
    }
}

void Personaje::manejarPasos()
{


    bool estaMoviendo = abs(_velocidad.x) > 0 || abs(_velocidad.y) > 0;

    if (estaMoviendo)
    {
        if (_relojPasos.getElapsedTime().asMilliseconds() > 100)
        {
            if (_footprints.getStatus() != sf::Sound::Playing)
            {
                _footprints.play();
            }
        }
    }

    else if (_footprints.getStatus() == sf::Sound::Playing)
    {
        _footprints.stop();
    }
}

sf::FloatRect Personaje::getColisionBounds() const
{

    sf::FloatRect localRect = _sprite.getLocalBounds();

    return getTransform().transformRect(localRect);

}

void Personaje::setPosicion(float uno, float dos)
{
    setPosition(uno, dos);
}


////Espada

void Personaje::updateEspada(const Raton& mouse)
{
    _espada.update(mouse.getPosicion(), getPosition());
}

bool Personaje::atacar(Mob& enemigo, float fuerzaEmpuje, float deltatime)
{
    chocar(enemigo._colision);

    sf::Vector2f empuje (0.f, 0.f);

    if (getColisionador().detectorDeColision(enemigo._colision, empuje.x, empuje.y))
    {
        enemigo.move(-empuje.x * fuerzaEmpuje, -empuje.y * fuerzaEmpuje);
        move(empuje.x * fuerzaEmpuje, empuje.y * fuerzaEmpuje);

        float danio = 50;
        enemigo.bajarVida(danio);
    }

    return (enemigo.getVida() <= 0);
}

void Personaje::setVolumen (float Volumen)
{
    _footprints.setVolume(Volumen);
}

void Personaje::setItemEnMano(const sf::Sprite& spriteItem, int idItem)
{
    _spriteHerramienta = spriteItem;
    _spriteHerramienta.setOrigin(0, 32);


    if (idItem >= 6 && idItem <= 8) {
        _esEspada = true;
    } else {
        _esEspada = false;
    }

    _tieneHerramienta = true;

    if (_atacando)
    {
        _spriteHerramienta.setRotation(_anguloAtaque);
    }
    else
    {
        _spriteHerramienta.setRotation(0);
    }
}

bool Personaje::iniciarAtaque()
{

        if (_atacando)
        {
            return false;
        }


        _atacando = true;
        if (_esEspada) {
            _anguloAtaque = -60.0f;
        }
        else {
            _anguloAtaque = 0.0f;
        }

        _spriteHerramienta.setRotation(_anguloAtaque);

        return true;

}

void Personaje::actualizarAnimacionAtaque(float deltatime)
{
    if (_atacando)
    {
        float dt = deltatime / 1000.0f;
        float velocidad = (_esEspada) ? 1200.0f : 600.0f;

        _anguloAtaque += velocidad * dt;

        float limiteAngulo = (_esEspada) ? 120.0f : 100.0f;

        if (_anguloAtaque >= limiteAngulo) {
            _atacando = false;
            float reposo = (_esEspada) ? -30.0f : 0.0f;
            _spriteHerramienta.setRotation(reposo);
            return;
        }

        float rotacionFinal = _anguloAtaque;

        if (_movimiento == 1) {

            rotacionFinal = _anguloAtaque - 120.0f;
        }
        else if (_movimiento == 0) {
            rotacionFinal = -_anguloAtaque - 180;
        }
        

        if (_spriteHerramienta.getScale().x < 0) {
            _spriteHerramienta.setRotation(-rotacionFinal);
        } else {
            _spriteHerramienta.setRotation(rotacionFinal);
        }
    }
}
