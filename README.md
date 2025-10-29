# 🧱 Proyecto Tilemap con SFML

Este proyecto es una base para juegos 2D desarrollados en **C++** con **SFML**, que permite cargar mapas creados en **Tiled** (en formato `.json`), dibujarlos en pantalla y manejar colisiones entre el personaje y el entorno.

---

## 🚀 Características principales

- 🗺️ **Carga de mapas desde Tiled (.json)**  
  Soporta múltiples capas (suelo, objetos, etc.), cada una renderizada por separado.

- 🎨 **Manejo de múltiples tilesets**  
  Carga texturas diferentes (por ejemplo, `suelo.png` y `items.png`) y las combina en el mismo mapa.

- 🧍 **Personaje con movimiento**  
  El jugador puede moverse libremente, con detección de dirección y animación.

- 🪨 **Sistema de colisiones**  
  Los tiles con ciertos IDs definidos en Tiled generan automáticamente **colisionadores**, que se almacenan en un vector y se verifican en el juego.

- 🪄 **Integración simple con SFML**  
  Uso directo de `sf::Sprite`, `sf::Texture` y `sf::FloatRect` para una implementación clara y flexible.

---

## 📂 Estructura del proyecto
