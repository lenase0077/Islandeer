#pragma once
#include <SFML/Graphics.hpp>
#include "Mob.h"
#include "Item.h"
#include "FabricaEstructuras.h"
#include "Loot.h"
#include "InventarioIntefaz.h"
#include <list>
#include <ctime>
#include "Comando.h"

enum class EstadoAnimal{
    Divagando,
    EsReposo,
    Huyendo
};

class Animal : public Mob
{
    public:
        Animal(const sf::Texture& textura);
        Animal(const sf::Texture& textura , sf::Vector2f PosicionInicial);
        void update(sf::Vector2f& Posicionpersonaje, float deltatime);
        void enReposo (float deltaTime);
        void recibirAtaqueDeEspada();
        bool caracteristicasDelAnimal(int idLoot, bool produceLeche);
        void soltarLoot (FabricaItems& fabItems, std::list<Loot>& listaLoot);
        bool intentarOrdeniar (const sf::Vector2f& Posicionpersonaje, Item* itemEnMano, FabricaItems& fabItems, InventarioInterfaz& Inv);

    private:
        EstadoAnimal _estadoActual;
        float _tiempoEnEstado;
        float _tiempoEnReposo;
        float _tiempoDivagacion;
        int _idLootAlMorir;
        bool _produceLeche;
        bool _lecheDisponible;
        float _tiempoRecargaLeche;
        void actualizarSpriteAnimacion (float deltaTime);
        bool _golpeadoPorEspada = false;
        void huir(sf::Vector2f& Posicionpersonaje, float aceleracion);
        void actualizarDireccion();
        void recibirDanio();
};
