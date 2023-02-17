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
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    pthread_t userInput;
    thread_data tdata = {0};

    // Assign a thread to user input so they can always break out of the loop
    while (1)
    {
        // Lock the mutex so that the user input thread can't access the shared data
        pthread_mutex_lock(&mutex);
        // Create the thread
        pthread_create(&userInput, NULL, GetUserInput, &tdata);
        // Unlock the mutex so that the user input thread can access the shared data
        pthread_mutex_unlock(&mutex);
        // Wait for the thread to finish
        pthread_join(userInput, NULL);
        // If the user input thread has set the result to 1, then break out of the loop
        if (tdata.result == 1)
        {
            break;
        }
        // If the user input thread hasn't set the result to 1, then continue the loop

        if (i % 2 == 0)
        {
            Move *move;
            move = RecurseCalculate(board, NULL, 1, 0, "White");
            PrintMove(move);
            PlayMove(board, move);
            PrintBoard(board);
            free(move);
        }
        else
        {
            Move *move;
            move = RecurseCalculate(board, NULL, 1, 0, "Black");
            PrintMove(move);
            PlayMove(board, move);
            PrintBoard(board);
            free(move);
        }

        i++;
    }
    pthread_mutex_destroy(&mutex);
}

// This will be the function that will be called by the thread
void *GetUserInput(void *arg)
{
    thread_data *tdata = (thread_data *)arg;
    printf("Enter e to exit: ");
    char *input = (char *)malloc(sizeof(char) * 10);
    scanf("%s", input);
    if (strcmp(input, "e") == 0)
    {
        tdata->result = 1;
    }
    free(input);
    return NULL;
}

// Will need to look at all available pieces, generate all possible moves, and then fire off recursive chains for each and scoring each one
Move *RecurseCalculate(struct Square **board, Move *firstMove, int depth, int count, char *color)
{
    Move *bestMove = (Move *)malloc(sizeof(Move));
    if (count == depth)
    {
        free(bestMove);
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
            printf("j: %d", j);
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
            free(move);
            j++;
        }
        FreeList(legalMoves);
    }
    free(allySquares);
    Node *node = moves->head;
    while (node != NULL)
    {
        bestMove = node->data;
        if (node->data != NULL)
        {
            free(node->data);
        }
        node = node->next;
    }

    FreeList(moves);

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

void Cycle(struct Square **board, Square square)
{
    if (square.piece == NULL)
    {
        return;
    }
    List *legalMoves = GetAllPawnMoves(board, &square);
    Node *node = legalMoves->head;
    // PrintMoves(legalMoves, &square);
    while (node != NULL)
    {
        Move *move = (Move *)malloc(sizeof(Move));
        move->start = &square;
        move->end = node->data;
        PlayMove(board, move);
        free(move);
        break;
    }

    FreeList(legalMoves);
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
    if (move == NULL || move->start == NULL || move->end == NULL)
    {
        return;
    }

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
