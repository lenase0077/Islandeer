#pragma once
#include <SFML/Graphics.hpp>
#include "string"

class TextoFlotante : public sf::Drawable, public sf::Transformable
{
private:
    sf::Text _texto;
    sf::Text _sombra;
    float _tiempoDeLectura;
    float _duracionFade;
    float _tiempoTranscurrido;
    bool _estadestruido;

public:
    TextoFlotante(const sf::Font& fuente, const std::string& mensaje, float posX, float posY);
    TextoFlotante(const sf::Font& fuente, const std::string& mensaje, float posX, float posY, float duracion);
    void update (float deltaTime);
    bool estaDestruido() const;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
