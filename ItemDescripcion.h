#pragma once
#include <cstring>
#include "SeleccionRectangulo.h"

class ItemDescripcion : public sf::Drawable
{
    public:
        ItemDescripcion(float x , float y , int anchoMax = 400);
        ItemDescripcion();
        void setDescripcion (std::string descripcion);
        void setTitulo (std::string titulo);
        std::string getDescripcion();
        std::string getTitulo();
        void EstablecerPosicion (float x , float y);
        void ActualizarDimensiones();
        bool getVisible();
        void setVisible(bool nuevoEstado);

    private:
        ///Graficos
        sf::RectangleShape _fondo;
        sf::Text _titulo;
        sf::Text _descripcion;
        sf::Font _fuente;
        bool _visible;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        ///Posicion y tamanio
        float _anchoMax;
        float _x , _y;
        float _margen;

        ///Textos
        std::string _textoDescripcion;
        std::string _textoTitulo;
};

