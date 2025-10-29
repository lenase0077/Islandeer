#pragma once
#include <SFML/Graphics.hpp>

class SeleccionRectangulo{
private:
    float _x1, _x2, _y1, _y2;
    bool _seleccionado;
public:
    bool estaDentro(float MouseX, float MouseY, bool condicionSeleccionado);
    SeleccionRectangulo(float x1,float x2,float y1,float y2);
    SeleccionRectangulo();

    float get_x1();
    float get_x2();
    float get_y1();
    float get_y2();
    bool get_seleccionado();

    void set_x1(float x1);
    void set_x2(float x2);
    void set_y1(float y1);
    void set_y2(float y2);
    void set_dimenciones(float x1,float x2,float y1,float y2);
    void set_seleccionado(bool seleccionado);
};
