#include "DisplayGame.h"

int main()
{
    DisplayGame game(5); //board size (3,5,7,9...)
    game.start(1); // 1 - 1 player, 2 - 2 player
    return 0;
}
