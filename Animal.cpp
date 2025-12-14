#include "Animal.h"
#include <iostream>
using namespace std;

Animal::Animal(const sf::Texture& textura)
    : Mob()
{
    _colision.setID("Animal");
    setTexture(textura);
    setScale(0.8, 0.8);
    setTextureRect(sf::IntRect(0,0,32,32));
    setVida(100);
    _idLootAlMorir = -1;
    _idLootSecundario= -1;
    _produceLeche = false;
    _lecheDisponible = false;
    _tiempoRecargaLeche = 0;
    _accionGallina = 0;

    _tiempoDivagar = (float)(rand() % (15 - 8 + 1) + 4) * 1000.0f;
    _tiempoEnReposo = (float)(rand() % (5 - 2 + 1) + 2) * 1000.0f;

    if (rand() % 2 == 0)
    {
        _estadoActual = EstadoAnimal::EsReposo;
        _frameActual = 0;
        _tiempoEnEstado = clamp(rand() , 0 , (int)_tiempoEnReposo);
    }

    else
    {
        _estadoActual = EstadoAnimal::Divagando;
        _frameActual = 0;
        _tiempoEnEstado = clamp(rand() , 0 , (int)_tiempoEnReposo);
    }
}

Animal::Animal(const sf::Texture& textura, sf::Vector2f PosicionInicial)
    : Mob()
{
    _colision.setID("Animal");
    setPosition(PosicionInicial);
    setTexture(textura);

    sf::Vector2u tamanoTextura = textura.getSize();

    if (tamanoTextura.x <= 64)
    {
        //Gallina
        setTextureRect(sf::IntRect(0, 0, 16, 16));
        setOrigin(8, 8);
        setScale(1.5f, 1.5f);
    }
    else
    {
        //Vaca-Oveja-Cerdo
        setTextureRect(sf::IntRect(0, 0, 32, 32));
        setOrigin(16, 16);
        setScale(1.f, 1.f);
    }

    setVida(100);
    _idLootAlMorir = -1;
    _idLootSecundario = -1;
    _produceLeche = false;
    _lecheDisponible = false;
    _tiempoRecargaLeche = 0;
    _accionGallina = 0;

    _tiempoDivagar = clamp(rand(), 0, 100000);
    _tiempoEnReposo = clamp (rand (), 0, 5000);

    if (rand() % 2 == 0)
    {
        _estadoActual = EstadoAnimal::EsReposo;
        _frameActual = 1;
        _tiempoEnEstado = clamp(rand(), 0, (int)_tiempoEnReposo);
    }

    else
    {
        _estadoActual = EstadoAnimal::Divagando;
        _frameActual = 0;
        _tiempoEnEstado = clamp(rand(), 0, (int)_tiempoEnReposo);
    }
}

void Animal::enReposo (float deltaTime)
{
    setVelocidad({0.0f, 0.0f}); // Usamos setVelocidad

    bool esGallina (_idLootAlMorir == 43);

    if (esGallina)
    {
        _tiempoDeAnimar += deltaTime;

        float velocidadFrame = (_accionGallina == 1) ? 200.0f : 800.0f;

        if (_tiempoDeAnimar >= velocidadFrame)
        {
            _frameActual++;
            if (_frameActual >= 4)
            {
                _frameActual = 0;
            }
            _tiempoDeAnimar -= velocidadFrame;
        }

        if (_accionGallina == 1)
        {
            setFrame(6, _frameActual);
        }

        else
        {
            setFrame(4, _frameActual);
        }
    }

    else
    {
        _tiempoDeAnimar += deltaTime;

        if (_tiempoDeAnimar >= 5000)
        {
            if (_frameActual == 0)
            {
                _frameActual = 1;
            }
            else
            {
                _frameActual = 0;
            }
            _tiempoDeAnimar -= 5000;
        }
        setFrame(4, _frameActual);
    }
}

void Animal::recibirAtaqueDeEspada()
{
    _estadoActual = EstadoAnimal::Huyendo;
    _tiempoEnEstado = 0.f;
    _golpeadoPorEspada = true;
}

void Animal::actualizarSpriteAnimacion (float deltaTime)
{
    _tiempoDeAnimar += deltaTime;

    if (_tiempoDeAnimar >= 250)
    {
        _frameActual++;
        if (_frameActual >= 4)
        {
            _frameActual = 0;
        }
        _tiempoDeAnimar -= 250;
    }

    int filaSpriteY = 0;

    switch(_direccionActual)
    {
    case DireccionMob::Abajo:
        filaSpriteY = 0;
        break;
    case DireccionMob::Izquierda:
        filaSpriteY = 1;
        break;
    case DireccionMob::Arriba:
        filaSpriteY = 2;
        break;
    case DireccionMob::Derecha:
        filaSpriteY = 3;
        break;
    }
    setFrame(filaSpriteY, _frameActual);
}

void Animal::update(sf::Vector2f& Posicionpersonaje, float deltatime)
{

    if (_tiempoFlashDanio > 0)
    {
        _tiempoFlashDanio -= deltatime / 1000.0f; // Restamos tiempo

        if (_tiempoFlashDanio <= 0)
        {
            setColor(sf::Color::White); // Volver a color normal
            _tiempoFlashDanio = 0;
        }
    }


    updateColision();
    _tiempoEnEstado += deltatime;

    float DistanciaJugador = calcularDistancia(Posicionpersonaje, getPosition());

    // --- LÓGICA DE DETECCIÓN Y CAMBIO DE ESTADO (PRIORIDAD) ---

    // 2. Fin de Huida por Proximidad (solo si no fue golpeado)
    if (_estadoActual == EstadoAnimal::Huyendo)
    {
        bool jugadorLejos = DistanciaJugador > 200;
        bool animalCansado = _tiempoEnEstado > 10000;

        if (jugadorLejos||animalCansado)
        {
            _estadoActual = EstadoAnimal::Divagando;
            _tiempoEnEstado = 0.f;
            _golpeadoPorEspada = false;
        }
    }

    // --- EJECUCION DEL ESTADO ACTUAL ---

    if (_estadoActual == EstadoAnimal::Huyendo)
    {
        huir(Posicionpersonaje, 1.5f);
        actualizarDireccion();
        actualizarSpriteAnimacion(deltatime);
    }
    else if (_estadoActual == EstadoAnimal::Divagando)
    {
        // divagar devuelve true si hay movimiento
        if (divagar(Posicionpersonaje, 0.5, deltatime))
        {
            actualizarDireccion();
            actualizarSpriteAnimacion(deltatime);

            // Lógica de probabilidad de entrar en reposo
            if (_tiempoEnEstado >= _tiempoDivagar)
            {
                if ((rand() % 100) == 0) // 1% de chance de entrar en reposo
                {
                    _estadoActual = EstadoAnimal::EsReposo;
                    _tiempoEnEstado = 0.f;
                    _frameActual = 0;

                    int decision = rand() % 3;
                    if (decision == 0) _accionGallina = 0; // Dormir
                    else _accionGallina = 1;               // Picar
                }
            }
        }
        else {
            // Si divagar es llamado, pero la velocidad es 0, mostramos el frame estático
            setFrame(4, 0);
        }
    }
    else if (_estadoActual == EstadoAnimal::EsReposo)
    {
        enReposo(deltatime);

        // Volver a divagar después del tiempo de reposo
        if (_tiempoEnEstado >= _tiempoEnReposo)
        {
            _estadoActual = EstadoAnimal::Divagando;
            _tiempoEnEstado = 0.f;
            _frameActual = 0;
        }
    }
    if (_produceLeche && !_lecheDisponible)
    {
        _tiempoRecargaLeche += deltatime;

        if (_tiempoRecargaLeche >= 10000)
        {
            _lecheDisponible = true;
            _tiempoRecargaLeche = 0;
        }
    }
}

void Animal::actualizarDireccion()
{
    if (abs(getVelocidad().x) > abs(getVelocidad().y))
    {
        if (getVelocidad().x > 0)
        {
            _direccionActual = DireccionMob::Derecha;
        }
        else
        {
            _direccionActual = DireccionMob::Izquierda;
        }
    }

    else
    {
        if (getVelocidad().y > 0)
        {
            _direccionActual = DireccionMob::Abajo;
        }
        else
        {
            _direccionActual = DireccionMob::Arriba;
        }
    }
}

void Animal::huir(sf::Vector2f& Posicionpersonaje, float aceleracion)
{
    // Vector: Animal - Personaje
    sf::Vector2f PosicionAnimal = getPosition();
    sf::Vector2f DireccionHuida = PosicionAnimal - Posicionpersonaje;

    float longitud = std::sqrt(DireccionHuida.x * DireccionHuida.x + DireccionHuida.y * DireccionHuida.y);

    if (longitud > 1.0f)
    {
        DireccionHuida.x /= longitud;
        DireccionHuida.y /= longitud;

        // Establecemos la velocidad de huida (usaremos aceleración 1.5f)
        setVelocidad({DireccionHuida.x * aceleracion, DireccionHuida.y * aceleracion});
    }
    else
    {
        // Si el jugador está tocando al animal, solo lo empujamos
        setVelocidad({aceleracion, 0.f});
    }
}

void Animal::recibirDanio()
{
    recibirAtaqueDeEspada();

    setColor(sf::Color(255, 0, 0));
    _tiempoFlashDanio = 0.2f;

}

bool Animal::caracteristicasDelAnimal(int idLoot, bool produceLeche, int idLootSecundario)
{
    _idLootAlMorir = idLoot;
    _produceLeche = produceLeche;
    _idLootSecundario = idLootSecundario;

    if (_produceLeche)
    {
        _lecheDisponible = true;
    }
    return true;
}

void Animal::soltarLoot (FabricaItems& fabItems, std::list<Loot>& listaLoot)
{
    if (_idLootAlMorir != -1)
    {
        listaLoot.emplace_back(fabItems, getPosition(), _idLootAlMorir);
    }

    if (_idLootSecundario != -1)
    {
        //Desplazamiento para que no se superpongan los loots
        sf::Vector2f posLootSecundario = getPosition();
        posLootSecundario.x += (rand() % 20) - 10;

        listaLoot.emplace_back(fabItems, getPosition(), _idLootSecundario);
    }
}

bool Animal::intentarOrdeniar (const sf::Vector2f& Posicionpersonaje, Item* itemEnMano, FabricaItems& fabItems, InventarioInterfaz& Inv)
{
    if (calcularDistancia(Posicionpersonaje, getPosition()) > 50)
    {
        return false;
    }

    if (_produceLeche && _lecheDisponible)
    {
        if (itemEnMano != nullptr)
        {
            if (itemEnMano->getID() == 28)
            {
                if (itemEnMano->getCantidad() == 1)
                {
                    std::unique_ptr<Item> nuevoItem = fabItems.crearItem(30);
                    *itemEnMano = *nuevoItem;
                }
                else
                {
                    Inv.agregarItem(30,1);
                    Inv.quitarItem(28,1);
                }

                _lecheDisponible = false;
                _tiempoRecargaLeche = 0;

                return true;
            }
        }
    }
    return false;
}

