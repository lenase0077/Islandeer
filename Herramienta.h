#pragma once
#include "Item.h"
#include <map>


enum class SonidoHerramienta { NINGUNO, HACHA, PICO, ESPADA };


class Herramienta : public Item {
private:
    float _durabilidad;
    float _danioBase;
    float _durabilidadMaxima;
    std::map<TipoMaterial, float> _multiplicadores; // Eficiencia contra materiales basicamente
    SonidoHerramienta _tipoSonido;

public:
    Herramienta(sf::Texture& textura, int id, float durabilidad, float danioBase);

    void agregarMultiplicador(TipoMaterial material, float valor);
    void setTipoSonido(SonidoHerramienta tipo);
    SonidoHerramienta getTipoSonido() const;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    // === POLIFORMISMO ALE ACA SOBREESCRIBO (jeje sabia que tenias curiosidad) ===

    float obtenerFuerza(TipoMaterial material) const override;
    void usar() override;
    bool estaRota() const override;
};
