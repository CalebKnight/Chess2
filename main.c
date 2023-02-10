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
    // PrintDirections(board[4][4].directions);
    struct Move *move = (struct Move *)malloc(sizeof(struct Move));
    move->start = &board[0][0];
    move->end = &board[3][0];
    PlayMove(board, move);
    free(move);
    PrintBoard(board);
    FreeBoard(board);
    return 0;
}
