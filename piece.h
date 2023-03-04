#ifndef PIECE_H
#define PIECE_H
typedef struct Piece
{
    char *name;
    char *color;
    char *symbol;
    int alive;
    int has_moved;
} Piece;

struct Piece *MakePiece(int x, int y);
struct Piece *CopyPiece(struct Piece *piece);
char *GetName(int x, int y);
char *GetIcon(int x, int y);
char *GetColor(int y);
int GetScore(Piece *piece, int count, int score);
void FreePiece(struct Piece *piece);
#endif