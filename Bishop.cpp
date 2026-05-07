#include "Bishop.h"

Bishop::Bishop(char c) : Piece(c)
{
}

char Bishop::getSymbol()
{
    if (color == 'W')
    {
        return 'B';
    }
    return 'b';
}

bool Bishop::isValidMove(int sr, int sc, int er, int ec, Board* board)
{
    if (myAbs(er - sr) != myAbs(ec - sc))
    {
        return false;
    }

    if (!board->isPathClear(sr, sc, er, ec))
    {
        return false;
    }

    return board->isEmpty(er, ec) || board->isEnemy(er, ec, color);
}