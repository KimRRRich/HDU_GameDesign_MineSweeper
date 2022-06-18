#include "Game.h"
#include <iostream>
using namespace std;

int main()
{
    Game Mine;
    while (Mine.window.isOpen()) {
        Mine.Run();
    }
}

