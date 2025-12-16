#include "Herramienta.h"

Herramienta::Herramienta(sf::Texture& textura, int id, float durabilidad, float danioBase)
    : Item(textura, id) // El constructor del orto que me daba problemas.
{
    _durabilidad = durabilidad;
    _danioBase = danioBase;
    _durabilidadMaxima = durabilidad;
    _tipoSonido = SonidoHerramienta::NINGUNO;

}

void Herramienta::agregarMultiplicador(TipoMaterial material, float valor) {
    _multiplicadores[material] = valor;
}

float Herramienta::obtenerFuerza(TipoMaterial material) const {
    if (_multiplicadores.count(material)) {
        return _danioBase * _multiplicadores.at(material);
    }
    return _danioBase;
}

void Herramienta::usar() {
    _durabilidad -= 1.0f;
}

bool Herramienta::estaRota() const {
    return _durabilidad <= 0;
}

void Herramienta::setTipoSonido(SonidoHerramienta tipo) {
    _tipoSonido = tipo;
}

SonidoHerramienta Herramienta::getTipoSonido() const {
    return _tipoSonido;
}

void Herramienta::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // 1. Dibujamos el Item normal (el sprite de la espada/pico)
    Item::draw(target, states);

    // 2. Calculamos el porcentaje de vida
    if (_durabilidadMaxima <= 0) return;
    float porcentaje = _durabilidad / _durabilidadMaxima;

     if (porcentaje >= 1.0f) return;

    // 3. Configuración de la Barra
    float anchoBarra = 24.0f;
    float altoBarra = 3.0f;

    // Posición relativa al sprite (ajustar según tu origen 16,16)
    float posX = -12.0f;
    float posY = 10.0f;

    // --- FONDO NEGRO ---
    sf::RectangleShape fondo(sf::Vector2f(anchoBarra, altoBarra));
    fondo.setFillColor(sf::Color(50, 50, 50));
    fondo.setPosition(posX, posY);

    // --- BARRA DE VIDA (COLOR) ---
    sf::RectangleShape barra(sf::Vector2f(anchoBarra * porcentaje, altoBarra));
    barra.setPosition(posX, posY);

    // Color según desgaste
    if (porcentaje > 0.5f)
        barra.setFillColor(sf::Color::Green);
    else if (porcentaje > 0.25f)
        barra.setFillColor(sf::Color::Yellow);
    else
        barra.setFillColor(sf::Color::Red);

    // 4. Aplicar transformaciones del padre
    states.transform *= getTransform();

    // 5. Dibujar
    target.draw(fondo, states);
    target.draw(barra, states);
}
