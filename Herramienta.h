#pragma once
#include "Item.h"
#include <map>

class Herramienta : public Item {
private:
    float _durabilidad;
    float _danioBase;
    std::map<TipoMaterial, float> _multiplicadores; // Eficiencia contra materiales basicamente

public:
    Herramienta(sf::Texture& textura, int id, float durabilidad, float danioBase);

    void agregarMultiplicador(TipoMaterial material, float valor);

    // === POLIFORMISMO ALE ACA SOBREESCRIBO (jeje sabia que tenias curiosidad) (OVERRIDE) ===

    float obtenerFuerza(TipoMaterial material) const override;
    void usar() override;
    bool estaRota() const override;
};
