#pragma once
#include "SFML/Graphics.hpp"
#include "Colisionador.h"

class Estructura : public sf::Transformable, public sf::Drawable
{


private:

    float _vida;
    Colisionador _colision;
    sf::Sprite _sprite;
    sf::Texture _textura;

public:

    Estructura( float posX, float posY);
    void actualizarTextura();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void recibirGolpe(float danio);
    Colisionador &getColisionador() {return _colision;};
    void update();
    bool estaDestruido() const;
    ~Estructura(){};

};
