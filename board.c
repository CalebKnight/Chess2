#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "square.h"
#include "board.h"
#include "piece.h"
#define AC_BLACK "\x1b[30m"
#define AC_RED "\x1b[31m"
#define AC_GREEN "\x1b[32m"
#define AC_YELLOW "\x1b[33m"
#define AC_BLUE "\x1b[34m"
#define AC_MAGENTA "\x1b[35m"
#define AC_CYAN "\x1b[36m"
#define AC_WHITE "\x1b[37m"
#define AC_NORMAL "\x1b[m"

struct Square **MakeBoard()
{
    Square **board = malloc(sizeof(Square) * 8 * 8);

    for (int i = 0; i < 8; i++)
    {
        // Initialise each row
        board[i] = malloc(sizeof(Square) * 8);
    }

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            board[i][j].x = i;
            board[i][j].y = j;
            board[i][j].name = GetSquareName(j, i);
            board[i][j].directions = GetMoves(board, j, i);
            if (i < 2 || i > 5)
            {
                board[i][j].piece = MakePiece(j, i);
            }
            else
            {
                board[i][j].piece = NULL;
            }
        }
    }
    return board;
}

Square *GetSquare(int x, int y, Square **board)
{
    return &board[x][y];
}

void PrintCords(Square **board)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            printf("\n%d", board[i][j].x);
            printf(" %d", board[i][j].y);
            printf(" %s", board[i][j].name);
        }
    }
    return;
}

void PrintBoard(Square **board)
{
    for (int i = 7; i > -1; i--)
    {
        printf("\n");
        for (int j = 0; j < 8; j++)
        {
            Piece *piece = board[i][j].piece;
            if (piece == NULL)
            {
                if ((i + j) % 2 == 0)
                    printf("%s ■ %s", AC_BLACK, AC_NORMAL);
                else
                    printf("%s ■ %s", AC_WHITE, AC_NORMAL);
            }
            else
            {

                printf("%s %s %s", (strcmp(piece->color, "White") ? AC_WHITE : AC_BLACK), piece->symbol, AC_NORMAL);
            }
        }
    }
    printf("\n");
    return;
}

void FreeBoard(Square **board)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            free(board[i][j].name);
            FreePiece(board[i][j].piece);
            FreeDirections(board[i][j].directions);
        }
        free(board[i]);
    }
    free(board);
    return;
}