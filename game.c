#include "game.h"
#include "board.h"
#include "piece.h"
#include "square.h"
#include "moves.h"
#include <stdio.h>
#include <stdlib.h>

void PlayMove(struct Square **board, struct Move *move)
{
    struct Square *start = move->start;
    struct Square *end = move->end;
    struct Piece *piece = start->piece;
    if (move->end->piece != NULL)
    {
        printf("You can't move there");
        return;
    }
    end->piece = piece;
    start->piece = NULL;
}