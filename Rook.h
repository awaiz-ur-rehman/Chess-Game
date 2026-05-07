#ifndef Rook_H
#define Rook_H

#include "Piece.h"
#include "Board.h"

class Rook : public Piece
{
public:
    Rook(char c);
    char getSymbol();
    bool isValidMove(int sr, int sc, int er, int ec, Board* board);
};

#endif
