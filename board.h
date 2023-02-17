#ifndef BOARD_H
#define BOARD_H
struct Square **MakeBoard();
struct Square **CopyBoard(struct Square **board);
void PrintCords(struct Square **board);
void PrintBoard(struct Square **board);
void FreeBoard(struct Square **board);
struct Square *GetSquare(int x, int y, struct Square **board);
#endif