#pragma once
#include <SFML/Graphics.hpp>
#include "string"

class TextoFlotante : public sf::Drawable, public sf::Transformable
{
private:
    sf::Text _texto;
    float _duracionTotal;
    float _tiempoTranscurrido;
    bool _estadestruido;

public:
    TextoFlotante(const sf::Font& fuente, const std::string& mensaje, float posX, float posY, sf::Color color = sf::Color::White);
    void update (float deltaTime);
    bool estaDestruido() const;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
