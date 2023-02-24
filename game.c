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

typedef struct thread_data
{
    int result;
} thread_data;

// This will be the while loop that makes the moves for each player
void RunGame(struct Square **board)
{
    int i = 0;

    // Assign a thread to user input so they can always break out of the loop
    while (1)
    {

        if (i % 2 == 0)
        {
            Move *move = RecurseCalculate(board, NULL, 1, 0, "White");
            PrintMove(move);
            PlayMove(board, move);
            PrintBoard(board);
        }
        else
        {
            Move *move = RecurseCalculate(board, NULL, 1, 0, "Black");
            PrintMove(move);
            PlayMove(board, move);
            PrintBoard(board);
        }
        if (GetUserInput() == 1)
        {
            break;
        }
        i++;
    }
}

// This will be the function that will be called by the thread
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

// Will need to look at all available pieces, generate all possible moves, and then fire off recursive chains for each and scoring each one
Move *RecurseCalculate(struct Square **board, Move *firstMove, int depth, int count, char *color)
{
    Move *bestMove;
    if (count == depth)
    {
        return firstMove;
    }
    Square **allySquares = GetAllPieces(board, color);
    List *moves = CreateList();
    for (int i = 0; i < 32; i++)
    {

        Square *allySquare = allySquares[i];

        if (allySquare == NULL)
        {
            continue;
        }
        List *legalMoves = GetAllPawnMoves(board, allySquare);
        if (strcmp(allySquare->piece->name, "Pawn") != 0 || legalMoves->size == 0)
        {
            FreeList(legalMoves);
            continue;
        }

        Node *node = legalMoves->head;
        int j = 0;
        while (node != NULL)
        {
            if (j > 10)
            {
                break;
            }
            Move *move = (Move *)malloc(sizeof(Move));
            move->start = allySquare;
            move->end = node->data;
            Square **newBoard = CopyBoard(board);
            PlayMove(newBoard, move);
            if (count == 0)
            {
                firstMove = move;
            }
            color = (strcmp(color, "White") == 0) ? "Black" : "White";
            Node *newMove = (Node *)malloc(sizeof(Node));
            newMove->data = RecurseCalculate(newBoard, firstMove, depth, count + 1, color);
            AppendList(moves, newMove);

            FreeBoard(newBoard);

            j++;
        }
        FreeList(legalMoves);
    }
    free(allySquares);
    Node *node = moves->head;
    while (node != NULL)
    {
        if (node->data != NULL)
        {
            bestMove = node->data;
        }
        node = node->next;
    }

    FreeListData(moves);

    free(moves);
    // Get all pieces
    // Get all moves
    // Recurse
    // Score
    // Return best move
    return (bestMove);
}

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

void PrintMoves(List *moves, Square *square)
{
    Node *node = moves->head;
    while (node != NULL)
    {
        printf("Start: %d %d", square->x, square->y);
        Square *move = (Square *)node->data;
        printf("Move: %d %d", move->x, move->y);
        node = node->next;
    }
}

void PlayMove(struct Square **board, struct Move *move)
{
    if (move == NULL)
        return;
    else if (move->start == NULL || move->end == NULL)
        return;
    int x = move->start->x;
    int y = move->start->y;
    int x2 = move->end->x;
    int y2 = move->end->y;
    board[y2][x2].piece = board[y][x].piece;
    board[y][x].piece = NULL;
}

List *GetAllPawnMoves(struct Square **board, Square *square)
{
    List *legalMoves = CreateList();
    if (strcmp(square->piece->color, "White") == 0)
    {
        AddWhitePawnMoves(square->directions, legalMoves);
    }
    else
    {
        AddBlackPawnMoves(square->directions, legalMoves);
    }
    return legalMoves;
}

void AddBlackPawnMoves(List **directions, List *legalMoves)
{
    List *bottom = directions[1];
    List *bottomLeft = directions[6];
    List *bottomRight = directions[7];
    if (bottom->size == 1)
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
        if (square->piece == NULL && square2->piece == NULL)
        {
            Node *node = CreateNode();
            node->data = square2;
            AppendList(legalMoves, node);
        }
    }
    if (bottomLeft->size == 1)
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
    if (bottomRight->size == 1)
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
        if (square->piece == NULL && square2->piece == NULL)
        {
            Node *node = CreateNode();
            node->data = square2;
            AppendList(legalMoves, node);
        }
    }
    if (topLeft->size == 1)
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
    if (topRight->size == 1)
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
