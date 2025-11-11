#pragma once
#include "Estructura.h"

class MesaCrafteo : public Estructura
{
    private:
        sf::Texture* _texturaFondoMenu;

    public:
        void mesaCrafteoUpdate();
};
