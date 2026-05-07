#ifndef King_H
#define King_H

#include "Piece.h"
#include "Board.h"

class King : public Piece
{
public:
    King(char c);
    char getSymbol();
    bool isValidMove(int sr, int sc, int er, int ec, Board* board);
};

#endif
