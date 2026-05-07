#include "Pawn.h"

Pawn::Pawn(char c) : Piece(c)
{
}

char Pawn::getSymbol()
{
    if (color == 'W')
    {
        return 'P';
    }
    return 'p';
}

bool Pawn::isValidMove(int sr, int sc, int er, int ec, Board* board)
{
    int dir;

    if (color == 'W')
    {
        dir = -1;
    }
    else
    {
        dir = 1;
    }

    if (sc == ec && er == sr + dir && board->isEmpty(er, ec))
    {
        return true;
    }

    if (sc == ec && er == sr + 2 * dir)
    {
        if (color == 'W' && sr == 6 && board->isEmpty(sr + dir, sc) && board->isEmpty(er, ec))
        {
            return true;
        }

        if (color == 'B' && sr == 1 && board->isEmpty(sr + dir, sc) && board->isEmpty(er, ec))
        {
            return true;
        }
    }

    if (myAbs(ec - sc) == 1 && er == sr + dir && board->isEnemy(er, ec, color))
    {
        return true;
    }

    return false;
}