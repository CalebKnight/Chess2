#include <stdio.h>
#include <stdlib.h>
#include "piece.h"

struct Piece *MakePiece(int x, int y)
{
    struct Piece *piece = malloc(sizeof(struct Piece));
    piece->name = GetName(x, y);
    piece->symbol = GetIcon(x, y);
    piece->color = GetColor(y);
    piece->alive = 1;
    piece->has_moved = 0;
    return piece;
}

char *GetName(int x, int y)
{
    if (y == 1 || y == 6)
    {
        return ("Pawn");
    }
    switch (x)
    {
    case 0:
    case 7:
        return ("Rook");
    case 1:
    case 6:
        return ("Knight");
    case 2:
    case 5:
        return ("Bishop");
    case 3:
        return ("Queen");
    case 4:
        return ("King");
    default:
        break;
    }
    return (" ");
}

char *GetIcon(int x, int y)
{
    if (y == 1 || y == 6)
    {
        if (y == 1)
        {
            return ("♙");
        }
        else
        {
            return ("♟");
        }
    }

    if (y == 7)
        switch (x)
        {
        case 0:
        case 7:
            return ("♜");
        case 1:
        case 6:
            return ("♞");
        case 2:
        case 5:
            return ("♝");
        case 3:
            return ("♛");
        case 4:
            return ("♚");
        default:
            break;
        }
    else
    {
        switch (x)
        {
        case 0:
        case 7:
            return ("♖");
        case 1:
        case 6:
            return ("♘");
        case 2:
        case 5:
            return ("♗");
        case 3:
            return ("♕");
        case 4:
            return ("♔");
        default:
            break;
        }
    }
    return (" ");
}

char *GetColor(int y)
{
    if (y == 1 || y == 0)
    {
        return ("Black");
    }
    else
    {
        return ("White");
    }
}

void FreePiece(struct Piece *piece)
{
    if (piece != NULL)
    {
        free(piece);
    }
    else
    {
        return;
    }
}