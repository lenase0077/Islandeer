#include <iostream>
#include "TextoFlotante.h"
using namespace std;

TextoFlotante::TextoFlotante(const sf::Font& fuente, const std::string& mensaje, float posX, float posY, sf::Color color)
{
    setPosition(posX, posY);

    _texto.setFont(fuente);
    _texto.setString(mensaje);
    _texto.setCharacterSize(10);
    _texto.setFillColor(color);

    ///Ponemos Bordes
    _texto.setOutlineColor(sf::Color::Black);
    _texto.setOutlineThickness(1.0f);

    ///Centramos el origen
    sf::FloatRect bounds = _texto.getLocalBounds();
    _texto.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);

    _duracionTotal = 5000.0f;
    _tiempoTranscurrido = 0.0f;
    _estadestruido = false;
}

void TextoFlotante::update (float deltaTime)
{
    if (_estadestruido == true) return;

    _tiempoTranscurrido += deltaTime;

    if (_tiempoTranscurrido >= _duracionTotal)
    {
        _estadestruido = true;
        return;
    }

    ///Movemos el texto hacia arriba
    move(0.f, -0.05f * deltaTime);

    ///Fade Out -> Si _duracionTotal es 255 de opacida: _tiempoTranscurrido es X opacidad que hay que RESTAR.
    float _tiempoRestante = _duracionTotal - _tiempoTranscurrido;

    int alpha = (_tiempoRestante / _duracionTotal) * 255;

    ///Aplicamos los colores
    sf::Color colorTexto = _texto.getFillColor();
    colorTexto.a = alpha;
    _texto.setFillColor(colorTexto);

    sf::Color colorBorde = _texto.getOutlineColor();
    colorBorde.a = alpha;
    _texto.setOutlineColor(colorBorde);
}

bool TextoFlotante::estaDestruido() const
{
    return _estadestruido;
}

void TextoFlotante::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(_texto, states);
}
