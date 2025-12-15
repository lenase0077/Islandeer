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

    ///Sombra
    _sombra = _texto;
    _sombra.setFillColor(sf::Color::Black);

    ///Centramos el origen
    sf::FloatRect bounds = _texto.getLocalBounds();
    _texto.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    _sombra.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);

    ///Tiempos
    _tiempoDeLectura = 3000.0f;
    _duracionFade = 1000.0f;
    _tiempoTranscurrido = 0.0f;
    _estadestruido = false;
}

TextoFlotante::TextoFlotante(const sf::Font& fuente, const std::string& mensaje, float posX, float posY, float duracion)
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

     ///Sombra
    _sombra = _texto;
    _sombra.setFillColor(sf::Color::Black);

    ///Centramos el origen
    sf::FloatRect bounds = _texto.getLocalBounds();
    _texto.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    _sombra.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);

    ///Tiempos
    _tiempoDeLectura = duracion;
    _duracionFade = 1000.0f;
    _tiempoTranscurrido = 0.0f;
    _estadestruido = false;
}


void TextoFlotante::update (float deltaTime)
{
    if (_estadestruido == true) return;

    _tiempoTranscurrido += deltaTime;

    float duracionTotal = _tiempoDeLectura + _duracionFade;

    if (_tiempoTranscurrido >= duracionTotal)
    {
        _estadestruido = true;
        return;
    }

    int alpha = 255;

    if (_tiempoTranscurrido <= _tiempoDeLectura)
    {
        alpha = 255;
    }

    else
    {
        ///FADEOUT
        float tiempoEnFade = _tiempoTranscurrido - _tiempoDeLectura;
        float FadeInverso = 1.0f - (tiempoEnFade / _duracionFade);
        alpha = (int)(FadeInverso * 255);
    }

    ///Aplicamos los colores
    sf::Color colorTexto = _texto.getFillColor();
    colorTexto.a = alpha;
    _texto.setFillColor(colorTexto);

    sf::Color colorBorde = _texto.getOutlineColor();
    colorBorde.a = alpha;
    _texto.setOutlineColor(colorBorde);

    ///Aplicamos la sombra
    sf::Color colorSombra = _sombra.getFillColor();
    colorSombra.a = alpha;
    _sombra.setFillColor(colorSombra);
}

bool TextoFlotante::estaDestruido() const
{
    return _estadestruido;
}

void TextoFlotante::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    //Creamos una copia temporal de la sombra para manipularla
    sf::Text sombraBlur = _sombra;

    //Obtenemos el alpha actual (la transparencia del fade out del update)
    int alphaActual = _sombra.getFillColor().a;

    // CAPA 1: Sombra cercana (Más fuerte)
    // Offset (1,1) - Opacidad 30% del alpha actual
    sombraBlur.setPosition(1.f, 1.f);
    sombraBlur.setFillColor(sf::Color(0, 0, 0, alphaActual * 0.3));
    target.draw(sombraBlur, states);

    // CAPA 2: Sombra media (Más suave)
    // Offset (2,2) - Opacidad 20%
    sombraBlur.setPosition(2.f, 2.f);
    sombraBlur.setFillColor(sf::Color(0, 0, 0, alphaActual * 0.2));
    target.draw(sombraBlur, states);

    // CAPA 3: Sombra lejana (Muy suave, el "borde difuso")
    // Offset (3,3) - Opacidad 10%
    sombraBlur.setPosition(3.f, 3.f);
    sombraBlur.setFillColor(sf::Color(0, 0, 0, alphaActual * 0.1));
    target.draw(sombraBlur, states);

    target.draw(_texto, states);
}
