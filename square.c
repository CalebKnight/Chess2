#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "piece.h"
#include "square.h"

// Takes in the co-ordinates of a square and returns a string of the square name
char *GetSquareName(int x, int y)
{
    char *name = malloc(sizeof(char) * 3);
    switch (x + 1)
    {
    case 1:
        name[0] = 'a';
        break;
    case 2:
        name[0] = 'b';
        break;
    case 3:
        name[0] = 'c';
        break;
    case 4:
        name[0] = 'd';
        break;
    case 5:
        name[0] = 'e';
        break;
    case 6:
        name[0] = 'f';
        break;
    case 7:
        name[0] = 'g';
        break;
    case 8:
        name[0] = 'h';
        break;
    default:
        break;
    }
    name[1] = y + '0';
    return name;
}
