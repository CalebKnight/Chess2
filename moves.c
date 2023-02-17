// for loop will run through a possible direction and check if it is a valid move

#include "moves.h"
#include "board.h"
#include "piece.h"
#include "square.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>

List **GetMoves(Square **board, int x, int y)
{
    List **directions = (List **)malloc(sizeof(List) * 8);
    for (int i = 0; i < 8; i++)
    {
        directions[i] = CreateList();
    }

    GetAllDirections(directions, board, x, y);

    // for (int i = 0; i < 8; i++)
    // {
    //     PrintDirection(directions[i]);
    // }

    return directions;
}

void FreeDirections(List **directions)
{
    for (int i = 0; i < 8; i++)
    {
        FreeList(directions[i]);
    }
    free(directions);
}

void PrintMove(Move *move)
{
    if (move != NULL && move->start != NULL && move->end != NULL)
    {
        printf("\nStart: %d %d", move->start->x, move->start->y);
        printf("\nMove: %d %d", move->end->x, move->end->y);
    }
    else
    {
        printf("\nMove is NULL");
    }
}

// Print all directions with the name of the direction it is heading first
void PrintDirections(List **directions)
{
    for (int i = 0; i < 8; i++)
    {
        switch (i)
        {
        case 0:
            printf("\nTop");
            break;
        case 1:
            printf("\nBottom");
            break;
        case 2:
            printf("\nLeft");
            break;
        case 3:
            printf("\nRight");
            break;
        case 4:
            printf("\nTop Left");
            break;
        case 5:
            printf("\nTop Right");
            break;
        case 6:
            printf("\nBottom Left");
            break;
        case 7:
            printf("\nBottom Right");
            break;
        default:
            break;
        }
        PrintDirection(directions[i]);
    }
}

// Print all the squares in a direction
void PrintDirection(List *direction)
{
    Node *node = GetHead(direction);

    while (node != NULL)
    {
        printf("\n");
        Square *square = (Square *)node->data;
        printf(square->name == NULL ? "NULL" : "%s", square->name);
        node = GetNext(node);
    }
}

// Get all the squares in a direction
// Need to exclude the square that the piece is on
// Need to make sure that we don't exceed the board
// Functions provide appropriate name for the direction we are checking

void GetAllDirections(List **directions, Square **board, int x, int y)
{

    for (int i = 1; i < 8; i++)
    {

        GetTop(directions[0], board, x, y, i);
        GetBottom(directions[1], board, x, y, i);
        GetLeft(directions[2], board, x, y, i);
        GetRight(directions[3], board, x, y, i);
        GetTopLeft(directions[4], board, x, y, i);
        GetTopRight(directions[5], board, x, y, i);
        GetBottomLeft(directions[6], board, x, y, i);
        GetBottomRight(directions[7], board, x, y, i);
    }
}

void GetTop(List *direction, Square **board, int x, int y, int i)
{
    if ((i + y) < 8)
    {
        Node *node = CreateNode();
        node->data = GetSquare(x, y + i, board);
        AppendList(direction, node);
    }
}

void GetBottom(List *direction, Square **board, int x, int y, int i)
{
    if ((y - i) > -1)
    {
        Node *node = CreateNode();
        node->data = GetSquare(x, y - i, board);
        AppendList(direction, node);
    }
}

void GetLeft(List *direction, Square **board, int x, int y, int i)
{
    if ((x - i) > -1)
    {
        Node *node = CreateNode();
        node->data = GetSquare(x - i, y, board);
        AppendList(direction, node);
    }
}

void GetRight(List *direction, Square **board, int x, int y, int i)
{
    if ((i + x) < 8)
    {
        Node *node = CreateNode();
        node->data = GetSquare(x + i, y, board);
        AppendList(direction, node);
    }
}

void GetTopLeft(List *direction, Square **board, int x, int y, int i)
{
    if ((i + y) < 8 && (x - i) > -1)
    {
        Node *node = CreateNode();
        node->data = GetSquare(x - i, y + i, board);
        AppendList(direction, node);
    }
}

void GetTopRight(List *direction, Square **board, int x, int y, int i)
{
    if ((i + y) < 8 && (i + x) < 8)
    {
        Node *node = CreateNode();
        node->data = GetSquare(x + i, y + i, board);
        AppendList(direction, node);
    }
}

void GetBottomLeft(List *direction, Square **board, int x, int y, int i)
{
    if ((y - i) > -1 && (x - i) > -1)
    {
        Node *node = CreateNode();
        node->data = GetSquare(x - i, y - i, board);
        AppendList(direction, node);
    }
}

void GetBottomRight(List *direction, Square **board, int x, int y, int i)
{
    if ((y - i) > -1 && (i + x) < 8)
    {
        Node *node = CreateNode();
        node->data = GetSquare(x + i, y - i, board);
        AppendList(direction, node);
    }
}
