#include <stdio.h>
#include <stdlib.h>
#include "piece.h"
#include "string.h"

// Creates a new piece based on the x and y coordinates (This is only used for the initial board)
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

// Copys a piece's data to a new piece
struct Piece *CopyPiece(struct Piece *piece)
{
    struct Piece *new_piece = malloc(sizeof(struct Piece));
    new_piece->name = piece->name;
    new_piece->symbol = piece->symbol;
    new_piece->color = piece->color;
    new_piece->alive = piece->alive;
    new_piece->has_moved = piece->has_moved;
    return new_piece;
}

// Gets the name of the piece based on the x and y coordinates
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

// Gets the icon of the piece based on the x and y coordinates (the icon is the unicode character)
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

// Gets the color of the piece based on the y coordinate
char *GetColor(int y)
{
    // If a piece is on the last two rows, it is black
    if (y == 6 || y == 7)
    {
        return ("Black");
    }
    else
    {
        return ("White");
    }
}

// Gets the score of the piece based on the piece's name, this is flipped using count so that it can be calculated as if it were the other player's turn
int GetScore(Piece *piece, int count, int score)
{

    if (piece == NULL)
    {
        score += 0;
    }
    else
    {
        char *name = piece->name;
        if (strcmp(name, "Pawn") == 0)
        {
            score += 1;
        }
        if (strcmp(name, "Knight") == 0 || strcmp(name, "Bishop") == 0)
        {
            score += 3;
        }
        if (strcmp(name, "Rook") == 0)
        {
            score += 5;
        }
        if (strcmp(name, "Queen") == 0)
        {
            score += 9;
        }
        if (strcmp(name, "King") == 0)
        {
            score += 100;
        }
    }
    if (count % 2 == 0)
    {
        return score;
    }
    else
    {
        return -score;
    }
}

// Frees the piece from memory
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
