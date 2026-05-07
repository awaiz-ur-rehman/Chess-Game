#ifndef Queen_H
#define Queen_H

#include "Piece.h"
#include "Board.h"

class Queen : public Piece
{
public:
    Queen(char c);
    char getSymbol();
    bool isValidMove(int sr, int sc, int er, int ec, Board* board);
};

#endif
