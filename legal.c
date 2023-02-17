#include "game.h"
#include "board.h"
#include "piece.h"
#include "square.h"
#include "moves.h"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"

int canPawnCapture(Square **board, Move move)
{
    int x = move.start->x;
    int y = move.start->y;
    int x2 = move.end->x;
    int y2 = move.end->y;
    if (board[x2][y2].piece != NULL)
    {
        if (board[x2][y2].piece->color != board[x][y].piece->color)
        {
            return 1;
        }
    }
    return 0;
}