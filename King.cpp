#include "King.h"

King::King(char c) : Piece(c)
{
}

char King::getSymbol()
{
    if (color == 'W')
    {
        return 'K';
    }
    return 'k';
}

bool King::isValidMove(int sr, int sc, int er, int ec, Board* board)
{
    if (myAbs(er - sr) <= 1 && myAbs(ec - sc) <= 1)
    {
        return board->isEmpty(er, ec) || board->isEnemy(er, ec, color);
    }

    return false;
}