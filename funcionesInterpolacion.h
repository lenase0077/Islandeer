#pragma once
#include <SFML/Graphics.hpp>
///Como la usamos bastante al calculo de interpolacion lineal, conocido popularmente como lerp era hora de replicarlo:
void lerp(sf::Vector2f& valorActual, const sf::Vector2f& objetivo, const float& factorInterpolacion);
void lerp(float& valorActual, const float& objetivo, const float& factorInterpolacion);
