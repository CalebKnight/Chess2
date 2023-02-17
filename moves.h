#ifndef MOVES_H
#define MOVES_H
#include <stdio.h>
#include <stdlib.h>
#include "square.h"
#include "board.h"
#include "list.h"

typedef struct Move
{
    struct Square *start;
    struct Square *end;
} Move;

List **GetMoves(struct Square **board, int x, int y);
void PrintDirection(List *direction);
void PrintDirections(List **directions);
void PrintMove(Move *move);
void GetAllDirections(List **directions, struct Square **board, int x, int y);
void GetTop(List *direction, struct Square **board, int x, int y, int i);
void GetBottom(List *direction, struct Square **board, int x, int y, int i);
void GetLeft(List *direction, struct Square **board, int x, int y, int i);
void GetRight(List *direction, struct Square **board, int x, int y, int i);
void GetTopLeft(List *direction, struct Square **board, int x, int y, int i);
void GetTopRight(List *direction, struct Square **board, int x, int y, int i);
void GetBottomLeft(List *direction, struct Square **board, int x, int y, int i);
void GetBottomRight(List *direction, struct Square **board, int x, int y, int i);
void FreeDirections(List **directions);
#endif