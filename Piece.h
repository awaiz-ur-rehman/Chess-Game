#ifndef Piece_H
#define Piece_H

int myAbs(int x);

class Board;

class Piece
{
protected:
    char color;

public:
    Piece(char c);
    virtual ~Piece();
    virtual char getSymbol() = 0;
    char getColor();
    virtual bool isValidMove(int sr, int sc, int er, int ec, Board* board) = 0;
};

#endif
