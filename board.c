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

// Makes the board and initialises all the squares
struct Square **MakeBoard()
{
    Square **board = malloc(sizeof(Square) * 8 * 8);

    for (int i = 0; i < 8; i++)
    {
        // Initialise each row
        board[i] = malloc(sizeof(Square) * 8);
    }

    // For this the second index is actually the x axis and the first is the y axis
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            board[i][j].x = j;
            board[i][j].y = i;
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

// Copies the board and returns a pointer to the new board
struct Square **CopyBoard(Square **board)
{
    Square **new_board = malloc(sizeof(Square) * 8 * 8);

    for (int i = 0; i < 8; i++)
    {
        // Initialise each row
        new_board[i] = malloc(sizeof(Square) * 8);
    }

    // For this the second index is actually the x axis and the first is the y axis
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            new_board[i][j].x = j;
            new_board[i][j].y = i;
            new_board[i][j].name = GetSquareName(j, i);
            new_board[i][j].directions = GetMoves(board, j, i);
            if (board[i][j].piece != NULL)
            {
                new_board[i][j].piece = MakePiece(j, i);
                new_board[i][j].piece->color = board[i][j].piece->color;
                new_board[i][j].piece->symbol = board[i][j].piece->symbol;
                new_board[i][j].piece->name = board[i][j].piece->name;
                new_board[i][j].piece->alive = board[i][j].piece->alive;
                new_board[i][j].piece->has_moved = board[i][j].piece->has_moved;
            }
            else
            {
                new_board[i][j].piece = NULL;
            }
        }
    }
    return new_board;
}

// Gets the square at the given co-ordinates
Square *GetSquare(int x, int y, Square **board)
{
    // X and Y are inverted here because the board is stored in a 2D array
    return &board[y][x];
}

// Prints the co-ordinates of all the squares
// Useful when debugging
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

// Prints the board
void PrintBoard(Square **board)
{
    for (int i = 7; i > -1; i--)
    {
        printf("\n");
        printf("%s %d %s", AC_WHITE, i, AC_NORMAL);
        for (int j = 0; j < 8; j++)
        {
            // This is intentionally inverted to place the chessboard the correct way up
            Piece *piece = board[i][j].piece;
            if (piece == NULL)
            {
                if ((i + j) % 2 == 0)
                    printf("%s ■ %s", AC_WHITE, AC_NORMAL);
                else
                    printf("%s ■ %s", AC_BLACK, AC_NORMAL);
            }
            else
            {
                // Not entirely sure why but inverting this fixes a litany of issues
                printf("%s %s %s", (strcmp(piece->color, "White") == 0 ? AC_WHITE : AC_BLACK), piece->symbol, AC_NORMAL);
            }
        }
    }
    printf("\n    A  B  C  D  E  F  G  H");
    printf("\n");
    return;
}

// Frees the board from memory
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