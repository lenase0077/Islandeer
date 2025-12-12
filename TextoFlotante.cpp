#include <iostream>
#include "TextoFlotante.h"
using namespace std;

TextoFlotante::TextoFlotante(const sf::Font& fuente, const std::string& mensaje, float posX, float posY)
{
    setPosition(posX, posY);

    _texto.setFont(fuente);
    _texto.setString(mensaje);
    _texto.setCharacterSize(8);

    sf::Texture& texturaFuente = (sf::Texture&)fuente.getTexture(8);
    texturaFuente.setSmooth(false);

    _texto.setFillColor(sf::Color::White);

    ///Ponemos Bordes
//    _texto.setOutlineColor(sf::Color::Black);
//    _texto.setOutlineThickness(1.5f);

    ///Centramos el origen
    sf::FloatRect bounds = _texto.getLocalBounds();
    _texto.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);

    _tiempoDeLectura = 3000.0f;

    float tiempoFadeOut = 1000.0f;

    _duracionTotal = _tiempoDeLectura + tiempoFadeOut
    ;
    _tiempoTranscurrido = 0.0f;
    _estadestruido = false;
}

TextoFlotante::TextoFlotante(const sf::Font& fuente, const std::string& mensaje, float posX, float posY, float& duracion)
{
    setPosition(posX, posY);

    _texto.setFont(fuente);
    _texto.setString(mensaje);
    _texto.setCharacterSize(8);
    _texto.setColor(sf::Color::White);

    sf::Texture& texturaFuente = (sf::Texture&)fuente.getTexture(8);
    texturaFuente.setSmooth(false);

    _texto.setFillColor(sf::Color::White);

    ///Ponemos Bordes
//    _texto.setOutlineColor(sf::Color::Black);
//    _texto.setOutlineThickness(1.5f);

    ///Centramos el origen
    sf::FloatRect bounds = _texto.getLocalBounds();
    _texto.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);

    float tiempoFadeOut = 1000.0f;

    _duracionTotal = duracion + tiempoFadeOut
    ;
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

    int alpha = 255;

    if (_tiempoTranscurrido > _tiempoDeLectura)
    {
        float tiempoRestante = _duracionTotal - _tiempoTranscurrido;
        float duracionFadeOut = _duracionTotal - _tiempoDeLectura;

        alpha = (int)((tiempoRestante / duracionFadeOut) * 255);
    }

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
