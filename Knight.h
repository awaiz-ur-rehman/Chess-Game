#ifndef Knight_H
#define Knight_H

#include "Piece.h"
#include "Board.h"

class Knight : public Piece
{
public:
    Knight(char c);
    char getSymbol();
    bool isValidMove(int sr, int sc, int er, int ec, Board* board);
};

#endif
