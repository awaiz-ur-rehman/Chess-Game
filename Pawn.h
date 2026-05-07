#ifndef Pawn_H
#define Pawn_H

#include "Piece.h"
#include "Board.h"

class Pawn : public Piece
{
public:
    Pawn(char c);
    char getSymbol();
    bool isValidMove(int sr, int sc, int er, int ec, Board* board);
};

#endif
