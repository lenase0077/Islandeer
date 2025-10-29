#include "SeleccionRectangulo.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

bool SeleccionRectangulo::estaDentro(float MouseX, float MouseY, bool condicionSeleccionado){
    bool entreX = ((MouseX > get_x1()) && (MouseX < get_x2()));
    bool entreY = ((MouseY > get_y1()) && (MouseY < get_y2()));
    if (condicionSeleccionado && entreX && entreY){
        set_seleccionado(true);
        return true;
    }
    else{
        set_seleccionado(false);
        return false;
    }
}

SeleccionRectangulo::SeleccionRectangulo(float x1,float x2,float y1,float y2){
    set_dimenciones(x1,x2,y1,y2);
}

SeleccionRectangulo::SeleccionRectangulo(){}

float SeleccionRectangulo::get_x1(){
    return _x1;
}
float SeleccionRectangulo::get_x2(){
    return _x2;
}
float SeleccionRectangulo::get_y1(){
    return _y1;
}
float SeleccionRectangulo::get_y2(){
    return _y2;
}
bool SeleccionRectangulo::get_seleccionado(){
    return _seleccionado;
}

void SeleccionRectangulo::set_x1(float x1){
    _x1 = x1;
}
void SeleccionRectangulo::set_x2(float x2){
    _x2 = x2;
}
void SeleccionRectangulo::set_y1(float y1){
    _y1 = y1;
}
void SeleccionRectangulo::set_y2(float y2){
    _y2 = y2;
}
void SeleccionRectangulo::set_dimenciones(float x1,float x2,float y1,float y2){
    set_x1(x1);
    set_x2(x2);
    set_y1(y1);
    set_y2(y2);
}
void SeleccionRectangulo::set_seleccionado(bool seleccionado){
    _seleccionado = seleccionado;
}
