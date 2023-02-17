#include <stdio.h>
#include <stdlib.h>
#include "moves.h"
#include "board.h"
#include "piece.h"
#include "square.h"
#include "list.h"
#include "game.h"

int main(int argc, char const *argv[])
{
    struct Square **board = MakeBoard();
    PrintBoard(board);
    RunGame(board);
    FreeBoard(board);
    return 0;
}
