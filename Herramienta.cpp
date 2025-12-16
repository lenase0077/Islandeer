#include "Herramienta.h"

Herramienta::Herramienta(sf::Texture& textura, int id, float durabilidad, float danioBase)
    : Item(textura, id) // El constructor del orto que me daba problemas.
{
    _durabilidad = durabilidad;
    _danioBase = danioBase;
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
