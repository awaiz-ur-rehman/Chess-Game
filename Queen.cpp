#include "Queen.h"

Queen::Queen(char c) : Piece(c)
{
}

char Queen::getSymbol()
{
    if (color == 'W')
    {
        return 'Q';
    }
    return 'q';
}

bool Queen::isValidMove(int sr, int sc, int er, int ec, Board* board)
{
    bool straight = sr == er || sc == ec;
    bool diagonal = myAbs(er - sr) == myAbs(ec - sc);

    if (!straight && !diagonal)
    {
        return false;
    }

    if (!board->isPathClear(sr, sc, er, ec))
    {
        return false;
    }

    return board->isEmpty(er, ec) || board->isEnemy(er, ec, color);
}