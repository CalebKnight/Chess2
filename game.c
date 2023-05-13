#include "game.h"
#include "board.h"
#include "piece.h"
#include "square.h"
#include "moves.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include <pthread.h>
#include <unistd.h>
#include "tree.h"

// This will be the while loop that makes the moves for each player
void RunGame(struct Square **board)
{
    int i = 0;
    while (1)
    {
        if (i % 2 == 0)
        {
            GameTree *tree = createGameTree(NULL);
            GetMove(board, tree, 0, 0, "white");
            printf("Tree size: %d\n", tree->size);
            freeGameTree(tree);
        }
        else
        {
        }
        if (GetUserInput() == 1)
        {
            break;
        }
        i++;
    }
}

// Gets user input to see if they want to exit the game
int GetUserInput()
{
    int val = 0;
    printf("Enter e to exit: ");
    char *input = (char *)malloc(sizeof(char) * 10);
    scanf("%s", input);
    if (strcmp(input, "e") == 0)
    {
        val = 1;
    }
    free(input);
    return val;
}

void *GetMove(struct Square **board, GameTree *tree, int depth, int count, char *color)
{

    Square **pieces = GetAllPieces(board, color);
    for (int i = 0; i < 32; i++)
    {
        List *moves = GetAllMoves(board, pieces[i]);
        //    TODO
        free(moves->items);
        free(moves);
    }
    free(pieces);
    return NULL;
}

// We will rewrite this function with a tree structure

struct RecurseArgs
{
    struct Square **board;
};

void *RecurseCalculate(void *arg)
{
    return NULL;
}

// Gets every single move a piece can make legally
List *GetAllMoves(struct Square **board, Square *square)
{
    List *moves = CreateList();
    if (strcmp(square->piece->name, "Pawn") == 0)
    {
        GetAllPawnMoves(board, square, moves);
    }
    return moves;
}

// Gets every piece of a certain color
Square **GetAllPieces(struct Square **board, char *color)
{
    Square **pieces = (Square **)malloc(sizeof(Square *) * 32);
    int i = 0;
    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            if (board[y][x].piece != NULL && strcmp(board[y][x].piece->color, color) == 0)
            {

                pieces[i] = &board[y][x];
                i++;
            }
        }
    }
    return pieces;
}

// Prints all the moves a piece can make
void PrintMoves()
{
    printf("Undefined");
}

// Plays a move on the board based on the start and end squares
Piece *PlayMove(struct Square **board, struct Move *move)
{
    Piece *pieceCopy;
    if (move == NULL)
        return NULL;
    else if (move->start == NULL || move->end == NULL)
        return NULL;
    int x = move->start->x;
    int y = move->start->y;
    int x2 = move->end->x;
    int y2 = move->end->y;
    // If this is a capture, a copy of the piece is returned
    // It is important this is copied to avoid memory leaks
    if (board[y2][x2].piece != NULL)
    {
        pieceCopy = CopyPiece(board[y2][x2].piece);
        free(board[y2][x2].piece);
    }
    else
    {
        pieceCopy = NULL;
    }
    board[y2][x2].piece = board[y][x].piece;
    board[y][x].piece = NULL;
    return (pieceCopy);
}

// Reverses a move on the board based on the start and end squares
void ReverseMove(struct Square **board, struct Move *move, Piece *capturedPiece)
{
    if (move == NULL)
        return;
    else if (move->start == NULL || move->end == NULL)
        return;
    int x = move->start->x;
    int y = move->start->y;
    int x2 = move->end->x;
    int y2 = move->end->y;
    board[y][x].piece = board[y2][x2].piece;
    if (capturedPiece != NULL)
    {
        // Use the captured piece to recreate the piece on the board
        board[y2][x2].piece = CopyPiece(capturedPiece);
        free(capturedPiece);
    }
    else
        board[y2][x2].piece = NULL;
}

// Gets every single move a pawn can make, this is unique for each color because pawns are unidirectional
void GetAllPawnMoves(struct Square **board, Square *square, List *moves)
{
    if (strcmp(square->piece->color, "White") == 0)
    {
        AddWhitePawnMoves(square->directions, moves);
    }
    else
    {
        AddBlackPawnMoves(square->directions, moves);
    }
}

// >= can be simplified but I left it like this as it makes it easier to understand logically
void AddBlackPawnMoves(List **directions, List *legalMoves)
{
    List *bottom = directions[1];
    List *bottomLeft = directions[6];
    List *bottomRight = directions[7];
    if (bottom->size >= 1)
    {
        Square *square = (Square *)bottom->head->data;
        if (square->piece == NULL)
        {
            Node *node = CreateNode();
            node->data = square;
            AppendList(legalMoves, node);
        }
    }
    if (bottom->size >= 2)
    {
        Square *square = (Square *)bottom->head->data;
        Square *square2 = (Square *)bottom->head->next->data;
        if (square->piece == NULL && square2->piece == NULL && square2->y == 4)
        {
            Node *node = CreateNode();
            node->data = square2;
            AppendList(legalMoves, node);
        }
    }
    if (bottomLeft->size >= 1)
    {
        Square *square = (Square *)bottomLeft->head->data;
        if (square->piece != NULL)
        {
            if (strcmp(square->piece->color, "White") == 0)
            {
                Node *node = CreateNode();
                node->data = square;
                AppendList(legalMoves, node);
            }
        }
    }
    if (bottomRight->size >= 1)
    {
        Square *square = (Square *)bottomRight->head->data;
        if (square->piece != NULL)
        {
            if (strcmp(square->piece->color, "White") == 0)
            {
                Node *node = CreateNode();
                node->data = square;
                AppendList(legalMoves, node);
            }
        }
    }
}
// >= can be simplified but I left it like this as it makes it easier to understand logically
void AddWhitePawnMoves(List **directions, List *legalMoves)
{
    List *top = directions[0];
    List *topLeft = directions[4];
    List *topRight = directions[5];
    if (top->size >= 1)
    {
        Square *square = (Square *)top->head->data;
        if (square->piece == NULL)
        {
            Node *node = CreateNode();
            node->data = square;
            AppendList(legalMoves, node);
        }
    }
    if (top->size >= 2)
    {
        Square *square = (Square *)top->head->data;
        Square *square2 = (Square *)top->head->next->data;
        if (square->piece == NULL && square2->piece == NULL && square2->y == 3)
        {
            Node *node = CreateNode();
            node->data = square2;
            AppendList(legalMoves, node);
        }
    }
    if (topLeft->size >= 1)
    {
        Square *square = (Square *)topLeft->head->data;
        if (square->piece != NULL)
        {
            if (strcmp(square->piece->color, "Black") == 0)
            {
                Node *node = CreateNode();
                node->data = square;
                AppendList(legalMoves, node);
            }
        }
    }
    if (topRight->size >= 1)
    {
        Square *square = (Square *)topRight->head->data;
        if (square->piece != NULL)
        {
            if (strcmp(square->piece->color, "Black") == 0)
            {
                Node *node = CreateNode();
                node->data = square;
                AppendList(legalMoves, node);
            }
        }
    }
}
