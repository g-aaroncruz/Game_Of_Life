#include "CImg.h"

#include "board.hpp"

#define size 500

int main()
{
    BOARD game(size);
    game.UpdateBoard();
    return 0;
}
