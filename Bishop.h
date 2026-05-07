#ifndef Bishop_H
#define Biahop_H

#include "Piece.h"
#include "Board.h"

class Bishop : public Piece
{
public:
    Bishop(char c);
    char getSymbol();
    bool isValidMove(int sr, int sc, int er, int ec, Board* board);
};

#endif
