#ifndef GAME_H
#define GAME_H

#include "square.h"
#include "board.h"
#include "piece.h"
#include "moves.h"

void PlayMove(struct Square **board, struct Move *move);
void RunGame(struct Square **board);
void PrintMoves(List *moves, Square *square);
Move *RecurseCalculate(struct Square **board, Move *firstMove, int depth, int count, char *color);
Square **GetAllPieces(struct Square **board, char *color);
List *GetAllPawnMoves(struct Square **board, Square *square);
void AddBlackPawnMoves(List **directions, List *legalMoves);
void AddWhitePawnMoves(List **directions, List *legalMoves);
int GetUserInput();
#endif