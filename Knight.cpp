#include "Knight.h"

Knight::Knight(char c) : Piece(c)
{
}

char Knight::getSymbol()
{
    if (color == 'W')
    {
        return 'N';
    }
    return 'n';
}

bool Knight::isValidMove(int sr, int sc, int er, int ec, Board* board)
{
    int dr = myAbs(er - sr);
    int dc = myAbs(ec - sc);

    if (!((dr == 2 && dc == 1) || (dr == 1 && dc == 2)))
    {
        return false;
    }

    return board->isEmpty(er, ec) || board->isEnemy(er, ec, color);
}