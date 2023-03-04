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
    // Initialise the board
    struct Square **board = MakeBoard();
    // Print the fresh board
    PrintBoard(board);
    // Run the game
    RunGame(board);
    // Free the board
    FreeBoard(board);
    return 0;
}
