#include "Game.h"
#include <iostream>
#include <ctime>

int main()
{

    srand(time(0));
    Game juego;
    juego.run();
    return 0;
}
