#pragma once
#include <SFML/Graphics.hpp>
#include <cstring>

class Colisionador{

    public:
        void draw(sf::RenderWindow &window);
        Colisionador();
        Colisionador(std::string ID);
        Colisionador(sf::FloatRect& rect);
        bool detectorDeColision( Colisionador& colisionado) const;
        bool detectorDeColision( Colisionador& colisionado , float& empujeX , float& empujeY) const;
        void setColision(sf::FloatRect);
        sf::FloatRect getColision();
        void setID (std::string ID);
        std::string getID ();

    private:
        std::string _ID;
        sf::FloatRect _colision;
        sf::RectangleShape rectanguloDebug;
};
