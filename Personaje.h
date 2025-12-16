#pragma once
#include "Colisionador.h"
#include <SFML/Graphics.hpp>
#include "Funciones.h"
#include <SFML/Audio.hpp>
#include "Espada.h"
#include "Raton.h"
#include "TileMap.h"
#include "Mob.h"
#include "BarraDeVida.h"


class Personaje: public sf::Drawable , public sf::Transformable
{
    public:
        Personaje(sf::Texture& _textura);
        Personaje(sf::Texture& _textura , int alto, int ancho);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void cmd(float deltatime);
        void update(float deltatime);
        void limite();
        void setVelocidad(float vx = 0.f, float vy = 0.f);
        Colisionador &getColisionador() {return _colision;};
        void animarPersonaje();
        void chocar(Colisionador& colision);
        sf::Vector2f getPosition() const;
        void Correr(sf::Vector2f& velocidad , float deltatime);
        bool getEstaCorriendo() const;
        void setEstaCorriendo(bool EstaCorriendo);
        void manejarPasos();
        sf::FloatRect getColisionBounds() const;
        void setPosicion(float uno , float dos);
        void setVida(float vida);
        float getVida();
        float getVidaMaxima() const { return _vidaMaxima; }

        void actuarEnBaseALaColision (std::string IDColision);
        void verificarColisiones(const TileMap& mapa);
        bool atacar(Mob& enemigo, float fuerzaEmpuje, float deltatime);
        float getEnergia();
        float getEnergiaMaxima() const { return 100.f; }

        ///Espada
        void updateEspada(const Raton& mouse);
        void setVolumen (float Volumen);

        void setItemEnMano(const sf::Sprite& spriteItem, int idItem);
        bool iniciarAtaque();
        void actualizarAnimacionAtaque(float deltatime);
        void quitarItemEnMano() { _tieneHerramienta = false; }
        sf::FloatRect getAreaAtaque() const;

                ///Hambre
        float getHambre();
        float getHambreMaxima() const { return _hambreMaxima; }
        void setHambre(float hambre);

        void envenenar(float tiempoSegundos);
        bool estaEnvenenado() const;

        void activarPoderDorado(float tiempo);
        bool tienePoderDorado() const;

    private:
        float _acumuladorEnergia = 0;
        bool _tocoEnemigo = false;
        float _vida;
        float _vidaMaxima;
        float _energia;
        Colisionador _colision;
        sf::FloatRect tamanio;
        sf::Vector2f _velocidad;
        sf::Sprite _sprite;
        Espada _espada;

        float _hambre;
        float _hambreMaxima;
        float _acumuladorHambre = 0;


        int _movimiento; ///0 -> Abajio
                         ///1 -> Ariiba
                         ///2 -> Izquierda
                         ///3 -> Derecha

        int _frameActual; ///Indice de la columna del sprite (0, 1, 2, 3)
        sf::Clock _animacion; ///Reloj para gestionar el tiempo de la animacion
        bool _estaCorriendo;
        sf::Sound _footprints;
        sf::SoundBuffer _footprintsBuffer;
        sf::Clock _relojPasos;

        /// == TEST DE HERRAMIENTAS NO DEFINITIVO
        sf::Sprite _spriteHerramienta;
        bool _atacando = false;
        float _anguloAtaque = 0.0f;
        bool _tieneHerramienta = false;
        bool _esEspada = false;

        ///CONTROL DE ANIMACIONES
        int _maxFrame = 0;
        int _minFrame = 3;
        bool _primerRecorridoParado;
        bool _primerRecorridoMoviendose;

        sf::SoundBuffer _bufferPoderDorado;
        sf::Sound _sonidoPoderDorado;



        float _tiempoVenenoRestante = 0.0f;
        float _acumuladorDanioVeneno = 0.0f;

        float _tiempoPoderDorado = 0.0f;
        float _acumuladorRegeneracion = 0.0f;
};
