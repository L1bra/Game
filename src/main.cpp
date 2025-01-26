#include "application.h"

int main()
{
    Application game;
    if (!game.init()) return -1;
    game.start();

    return 0;
}