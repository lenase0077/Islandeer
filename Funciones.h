#pragma once
#include <SFML/Graphics.hpp>

void setFrame(int fila , int columna, sf::Sprite& sprite);
void setFramePersonaje(int fila , int columna, sf::Sprite& sprite);
float calcularDistancia(const sf::Vector2f& pos1, const sf::Vector2f& pos2);
std::string AjustarStringAutomaticamente(std::string stringOriginal, float anchoPixeles, int anchoMax = 200);
