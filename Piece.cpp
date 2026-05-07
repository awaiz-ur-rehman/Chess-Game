#include "Piece.h"

int myAbs(int x)
{
    if (x < 0)
    {
        return -x;
    }
    return x;
}

Piece::Piece(char c)
{
    color = c;
}

Piece::~Piece()
{
}

char Piece::getColor()
{
    return color;
}