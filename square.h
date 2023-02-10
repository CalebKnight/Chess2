#ifndef SQUARE_H
#define SQUARE_H

#include "piece.h"
#include "moves.h"
#include "list.h"
typedef struct Square
{
    int x;
    int y;
    char *name;
    struct Piece *piece;
    List **directions;
} Square;

char *GetSquareName(int x, int y);
#endif