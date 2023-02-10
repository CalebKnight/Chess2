#ifndef GAME_H
#define GAME_H

#include "square.h"
#include "board.h"
#include "piece.h"
#include "moves.h"

void PlayMove(struct Square **board, struct Move *move);

#endif