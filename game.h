#ifndef GAME_H
#define GAME_H

#include "square.h"
#include "board.h"
#include "piece.h"
#include "moves.h"

Piece *PlayMove(struct Square **board, struct Move *move);
void ReverseMove(struct Square **board, struct Move *move, Piece *capturedPiece);
void RunGame(struct Square **board);
void PrintMoves();
void *RecurseCalculate(void *arg);
void *GetMove(struct Square **board, GameTree *tree, int depth, int count, char *color);
List *GetAllMoves(struct Square **board, Square *square);
Square **GetAllPieces(struct Square **board, char *color);
void GetAllPawnMoves(struct Square **board, Square *square, List *moves);
void AddBlackPawnMoves(List **directions, List *legalMoves);
void AddWhitePawnMoves(List **directions, List *legalMoves);
int GetUserInput();
#endif