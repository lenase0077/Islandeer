#pragma once
#include "Colisionador.h"
#include <SFML/Graphics.hpp>
#include "Funciones.h"
#include <SFML/Audio.hpp>
#include "Espada.h"
#include "Raton.h"
#include "TileMap.h"
#include "BarraDeVida.h"


class Personaje: public sf::Drawable , public sf::Transformable
{
    public:
        Personaje();
        Personaje(int alto, int ancho);

        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void cmd();
        void update();
        void limite();
        void setVelocidad(float vx = 0.f, float vy = 0.f);
        Colisionador &getColisionador() {return _colision;};
        void animar();
        void chocar(Colisionador& colision);
        sf::Vector2f getPosition() const;
        void Correr(sf::Vector2f& velocidad);
        bool getEstaCorriendo() const;
        void setEstaCorriendo(bool EstaCorriendo);
        void manejarPasos();
        sf::FloatRect getColisionBounds() const;
        void setPosicion(float uno , float dos);
        void setVida(float vida);
        float getVida();
        void actuarEnBaseALaColision (std::string IDColision);
        void verificarColisiones(const TileMap& mapa);


        ///Espada
        void updateEspada(const Raton& mouse);


    private:
        bool _tocoEnemigo = false;
        float _vida;
        float _vidaMaxima;
        float _energia;
        Colisionador _colision;
        sf::FloatRect tamanio;
        sf::Vector2f _velocidad;
        sf::Texture _textura;
        sf::Sprite _sprite;
        Espada _espada;
        BarraDeVida _barraVida;


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
};

