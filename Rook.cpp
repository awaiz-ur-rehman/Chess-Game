#include "Rook.h"

Rook::Rook(char c) : Piece(c)
{
}

char Rook::getSymbol()
{
    if (color == 'W')
    {
        return 'R';
    }
    return 'r';
}

bool Rook::isValidMove(int sr, int sc, int er, int ec, Board* board)
{
    if (sr != er && sc != ec)
    {
        return false;
    }

    if (!board->isPathClear(sr, sc, er, ec))
    {
        return false;
    }

    return board->isEmpty(er, ec) || board->isEnemy(er, ec, color);
}